#pragma once

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <iterator>

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    using value_type             = T;
    using allocator_type         = Allocator;
    using allocator_traits       = std::allocator_traits<allocator_type>;
    using size_type              = typename allocator_traits::size_type;
    using difference_type        = typename allocator_traits::difference_type;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = typename allocator_traits::pointer;
    using const_pointer          = typename allocator_traits::const_pointer;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    allocator_type alloc_;
    pointer data_;
    size_type size_;
    size_type capacity_;

    // ------------------------------------------------------------
    // Memory helpers
    // ------------------------------------------------------------

    static constexpr size_type max_size_static() noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    void check_allocation_size(size_type n) const {
        if (n > allocator_traits::max_size(alloc_)) {
            throw std::length_error("Vector too large");
        }
    }

    pointer allocate(size_type n) {
        if (n == 0) return nullptr;
        check_allocation_size(n);
        return allocator_traits::allocate(alloc_, n);
    }

    void deallocate(pointer p, size_type n) noexcept {
        if (p) allocator_traits::deallocate(alloc_, p, n);
    }

    void destroy_range(pointer first, pointer last) noexcept {
        while (first != last) {
            allocator_traits::destroy(alloc_, std::addressof(*first));
            ++first;
        }
    }

    template <typename InputIt>
    pointer allocate_and_copy(InputIt first, InputIt last, size_type& out_size) {
        out_size = static_cast<size_type>(std::distance(first, last));
        pointer new_data = allocate(out_size);
        pointer current = new_data;

        try {
            for (; first != last; ++first, ++current) {
                allocator_traits::construct(alloc_, std::addressof(*current), *first);
            }
        } catch (...) {
            destroy_range(new_data, current);
            deallocate(new_data, out_size);
            throw;
        }

        return new_data;
    }

    void reallocate(size_type new_capacity) {
        if (new_capacity == capacity_) return;

        pointer new_data = allocate(new_capacity);
        pointer current = new_data;

        try {
            for (size_type i = 0; i < size_; ++i, ++current) {
                allocator_traits::construct(
                    alloc_, std::addressof(*current),
                    std::move_if_noexcept(data_[i])
                );
            }
        } catch (...) {
            destroy_range(new_data, current);
            deallocate(new_data, new_capacity);
            throw;
        }

        destroy_range(data_, data_ + size_);
        deallocate(data_, capacity_);

        data_ = new_data;
        capacity_ = new_capacity;
    }

    template <typename... Args>
    void reallocate_and_emplace(size_type new_capacity, Args&&... args) {
        pointer new_data = allocate(new_capacity);
        pointer current = new_data;

        try {
            for (size_type i = 0; i < size_; ++i, ++current) {
                allocator_traits::construct(
                    alloc_, std::addressof(*current),
                    std::move_if_noexcept(data_[i])
                );
            }

            allocator_traits::construct(
                alloc_, std::addressof(*current),
                std::forward<Args>(args)...
            );
            ++current;
        } catch (...) {
            destroy_range(new_data, current);
            deallocate(new_data, new_capacity);
            throw;
        }

        destroy_range(data_, data_ + size_);
        deallocate(data_, capacity_);

        data_ = new_data;
        capacity_ = new_capacity;
        ++size_;
    }

    size_type growth_capacity(size_type min_needed = 0) const {
        if (capacity_ == 0) {
            return std::max<size_type>(1, min_needed);
        }

        size_type max = allocator_traits::max_size(alloc_);
        size_type new_cap = capacity_ * 2;
        if (new_cap < capacity_ || new_cap > max) {
            new_cap = max;
        }
        if (new_cap < min_needed) {
            new_cap = min_needed;
        }
        return new_cap;
    }

    template <typename InputIt>
    using IsNotIntegral = std::enable_if_t<!std::is_integral_v<InputIt>, int>;

public:
    // ------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------

    Vector() noexcept(std::is_nothrow_default_constructible_v<allocator_type>)
        : alloc_(), data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(const allocator_type& alloc) noexcept
        : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(size_type count, const allocator_type& alloc = allocator_type())
        : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {
        if (count == 0) return;

        data_ = allocate(count);
        capacity_ = count;

        pointer current = data_;
        try {
            for (; size_ < count; ++size_, ++current) {
                allocator_traits::construct(alloc_, std::addressof(*current));
            }
        } catch (...) {
            destroy_range(data_, current);
            deallocate(data_, capacity_);
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            throw;
        }
    }

    Vector(size_type count, const T& value,
           const allocator_type& alloc = allocator_type())
        : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {
        if (count == 0) return;

        data_ = allocate(count);
        capacity_ = count;

        pointer current = data_;
        try {
            for (; size_ < count; ++size_, ++current) {
                allocator_traits::construct(
                    alloc_, std::addressof(*current), value
                );
            }
        } catch (...) {
            destroy_range(data_, current);
            deallocate(data_, capacity_);
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            throw;
        }
    }

    template <typename InputIt, IsNotIntegral<InputIt> = 0>
    Vector(InputIt first, InputIt last,
           const allocator_type& alloc = allocator_type())
        : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {
        if (first == last) return;
        size_type new_size = 0;
        data_ = allocate_and_copy(first, last, new_size);
        size_ = new_size;
        capacity_ = new_size;
    }

    Vector(std::initializer_list<T> init,
           const allocator_type& alloc = allocator_type())
        : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {
        if (init.size() == 0) return;

        data_ = allocate(init.size());
        capacity_ = init.size();

        pointer current = data_;
        try {
            for (const auto& value : init) {
                allocator_traits::construct(
                    alloc_, std::addressof(*current), value
                );
                ++current;
                ++size_;
            }
        } catch (...) {
            destroy_range(data_, current);
            deallocate(data_, capacity_);
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            throw;
        }
    }

    Vector(const Vector& other)
        : alloc_(allocator_traits::select_on_container_copy_construction(
              other.alloc_)),
          data_(nullptr),
          size_(0),
          capacity_(0) {
        if (other.size_ == 0) return;

        data_ = allocate(other.size_);
        capacity_ = other.size_;

        pointer current = data_;
        try {
            for (; size_ < other.size_; ++size_, ++current) {
                allocator_traits::construct(
                    alloc_, std::addressof(*current), other.data_[size_]
                );
            }
        } catch (...) {
            destroy_range(data_, current);
            deallocate(data_, capacity_);
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            throw;
        }
    }

    Vector(Vector&& other) noexcept
        : alloc_(std::move(other.alloc_)),
          data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // ------------------------------------------------------------
    // Assignment
    // ------------------------------------------------------------

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        if constexpr (allocator_traits::propagate_on_container_copy_assignment::value) {
            if (alloc_ != other.alloc_) {
                clear();
                deallocate(data_, capacity_);
                data_ = nullptr;
                size_ = 0;
                capacity_ = 0;
            }
            alloc_ = other.alloc_;
        }

        if (other.size_ > capacity_) {
            Vector temp(other);
            swap(temp);
            return *this;
        }

        size_type i = 0;
        for (; i < size_ && i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        if (i < other.size_) {
            for (; i < other.size_; ++i) {
                allocator_traits::construct(alloc_, std::addressof(data_[i]), other.data_[i]);
            }
        } else {
            destroy_range(data_ + other.size_, data_ + size_);
        }
        size_ = other.size_;
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept(
        allocator_traits::propagate_on_container_move_assignment::value ||
        allocator_traits::is_always_equal::value) {
        if (this == &other) return *this;

        if constexpr (allocator_traits::propagate_on_container_move_assignment::value) {
            clear();
            deallocate(data_, capacity_);

            alloc_ = std::move(other.alloc_);
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        } else {
            if (alloc_ == other.alloc_) {
                clear();
                deallocate(data_, capacity_);

                data_ = other.data_;
                size_ = other.size_;
                capacity_ = other.capacity_;

                other.data_ = nullptr;
                other.size_ = 0;
                other.capacity_ = 0;
            } else {
                // Different non-propagating allocators: move elements
                if (other.size_ > capacity_) {
                    clear();
                    deallocate(data_, capacity_);
                    data_ = allocate(other.size_);
                    capacity_ = other.size_;
                }

                size_type i = 0;
                for (; i < size_ && i < other.size_; ++i) {
                    data_[i] = std::move(other.data_[i]);
                }
                if (i < other.size_) {
                    for (; i < other.size_; ++i) {
                        allocator_traits::construct(
                            alloc_, std::addressof(data_[i]),
                            std::move(other.data_[i])
                        );
                    }
                } else {
                    destroy_range(data_ + other.size_, data_ + size_);
                }
                size_ = other.size_;
                other.clear();
            }
        }

        return *this;
    }

    Vector& operator=(std::initializer_list<T> ilist) {
        assign(ilist.begin(), ilist.end());
        return *this;
    }

    // ------------------------------------------------------------
    // Destructor
    // ------------------------------------------------------------

    ~Vector() {
        clear();
        deallocate(data_, capacity_);
    }

    // ------------------------------------------------------------
    // Element access
    // ------------------------------------------------------------

    reference operator[](size_type pos) noexcept { return data_[pos]; }
    const_reference operator[](size_type pos) const noexcept { return data_[pos]; }

    reference at(size_type pos) {
        if (pos >= size_) throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= size_) throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    reference front() {
        if (empty()) throw std::out_of_range("front()");
        return data_[0];
    }
    const_reference front() const {
        if (empty()) throw std::out_of_range("front()");
        return data_[0];
    }

    reference back() {
        if (empty()) throw std::out_of_range("back()");
        return data_[size_ - 1];
    }
    const_reference back() const {
        if (empty()) throw std::out_of_range("back()");
        return data_[size_ - 1];
    }

    pointer data() noexcept { return data_; }
    const_pointer data() const noexcept { return data_; }

    // ------------------------------------------------------------
    // Iterators
    // ------------------------------------------------------------

    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }

    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cend() const noexcept { return data_ + size_; }

    // ------------------------------------------------------------
    // Reverse iterators
    // ------------------------------------------------------------

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    // ------------------------------------------------------------
    // Capacity
    // ------------------------------------------------------------

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
    size_type capacity() const noexcept { return capacity_; }
    size_type max_size() const noexcept { return allocator_traits::max_size(alloc_); }

    void reserve(size_type new_capacity) {
        if (new_capacity > capacity_) reallocate(new_capacity);
    }

    void shrink_to_fit() {
        if (size_ < capacity_) {
            if (size_ == 0) {
                clear();
                deallocate(data_, capacity_);
                data_ = nullptr;
                capacity_ = 0;
            } else {
                reallocate(size_);
            }
        }
    }

    // ------------------------------------------------------------
    // Modifiers
    // ------------------------------------------------------------

    void clear() noexcept {
        destroy_range(data_, data_ + size_);
        size_ = 0;
    }

    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            reallocate_and_emplace(
                growth_capacity(size_ + 1),
                std::forward<Args>(args)...
            );
            return back();
        }

        allocator_traits::construct(
            alloc_, std::addressof(data_[size_]),
            std::forward<Args>(args)...
        );
        ++size_;
        return back();
    }

    void push_back(const T& value) { emplace_back(value); }
    void push_back(T&& value) { emplace_back(std::move(value)); }

    void pop_back() {
        if (size_ == 0) return;
        --size_;
        allocator_traits::destroy(alloc_, std::addressof(data_[size_]));
    }

    void resize(size_type count) {
        if (count < size_) {
            while (size_ > count) pop_back();
            return;
        }

        if (count > size_) {
            reserve(count);
            while (size_ < count) emplace_back();
        }
    }

    void resize(size_type count, const T& value) {
        if (count < size_) {
            while (size_ > count) pop_back();
            return;
        }

        if (count > size_) {
            reserve(count);
            while (size_ < count) emplace_back(value);
        }
    }

    void assign(size_type count, const T& value) {
        clear();
        if (count > capacity_) {
            deallocate(data_, capacity_);
            data_ = allocate(count);
            capacity_ = count;
        }
        pointer current = data_;
        for (size_type i = 0; i < count; ++i, ++current) {
            allocator_traits::construct(alloc_, std::addressof(*current), value);
        }
        size_ = count;
    }

    template <typename InputIt, IsNotIntegral<InputIt> = 0>
    void assign(InputIt first, InputIt last) {
        clear();
        size_type new_size = static_cast<size_type>(std::distance(first, last));
        if (new_size > capacity_) {
            deallocate(data_, capacity_);
            data_ = allocate(new_size);
            capacity_ = new_size;
        }
        pointer current = data_;
        for (; first != last; ++first, ++current) {
            allocator_traits::construct(alloc_, std::addressof(*current), *first);
        }
        size_ = new_size;
    }

    void assign(std::initializer_list<T> ilist) {
        assign(ilist.begin(), ilist.end());
    }

    iterator insert(const_iterator pos, const T& value) {
        return emplace(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        return emplace(pos, std::move(value));
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        size_type index = static_cast<size_type>(pos - data_);
        if (index > size_) throw std::out_of_range("Vector::insert");

        if (count == 0) return data_ + index;

        if (size_ + count > capacity_) {
            size_type new_cap = growth_capacity(size_ + count);
            pointer new_data = allocate(new_cap);
            pointer dest = new_data;

            pointer src = data_;
            for (size_type i = 0; i < index; ++i, ++src, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            }

            for (size_type i = 0; i < count; ++i, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), value);
            }

            for (size_type i = index; i < size_; ++i, ++src, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            }

            destroy_range(data_, data_ + size_);
            deallocate(data_, capacity_);

            data_ = new_data;
            capacity_ = new_cap;
            size_ += count;
            return data_ + index;
        } else {
            // Enough capacity: shift tail and fill
            pointer pos_ptr = data_ + index;
            pointer old_end = data_ + size_;
            pointer new_end = data_ + size_ + count;

            if (count <= static_cast<size_type>(old_end - pos_ptr)) {
                // Move tail part into uninitialized space
                for (pointer p = old_end - 1; p >= pos_ptr; --p) {
                    allocator_traits::construct(alloc_, std::addressof(*(p + count)), std::move_if_noexcept(*p));
                    allocator_traits::destroy(alloc_, std::addressof(*p));
                    if (p == pos_ptr) break;
                }
                for (size_type i = 0; i < count; ++i) {
                    allocator_traits::construct(alloc_, std::addressof(pos_ptr[i]), value);
                }
            } else {
                size_type tail = static_cast<size_type>(old_end - pos_ptr);
                pointer p = old_end;
                // Move tail into new positions
                for (size_type i = 0; i < tail; ++i, --p) {
                    allocator_traits::construct(alloc_, std::addressof(*(p + count - 1)), std::move_if_noexcept(*(p - 1)));
                    allocator_traits::destroy(alloc_, std::addressof(*(p - 1)));
                }
                // Fill all gap with value
                for (size_type i = 0; i < count; ++i) {
                    allocator_traits::construct(alloc_, std::addressof(pos_ptr[i]), value);
                }
            }

            size_ += count;
            return data_ + index;
        }
    }

    template <typename InputIt, IsNotIntegral<InputIt> = 0>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_type index = static_cast<size_type>(pos - data_);
        if (index > size_) throw std::out_of_range("Vector::insert");

        if (first == last) return data_ + index;

        size_type count = static_cast<size_type>(std::distance(first, last));

        if (size_ + count > capacity_) {
            size_type new_cap = growth_capacity(size_ + count);
            pointer new_data = allocate(new_cap);
            pointer dest = new_data;

            pointer src = data_;
            for (size_type i = 0; i < index; ++i, ++src, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            }

            for (; first != last; ++first, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), *first);
            }

            for (size_type i = index; i < size_; ++i, ++src, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            }

            destroy_range(data_, data_ + size_);
            deallocate(data_, capacity_);

            data_ = new_data;
            capacity_ = new_cap;
            size_ += count;
            return data_ + index;
        } else {
            pointer pos_ptr = data_ + index;
            pointer old_end = data_ + size_;
            pointer new_end = data_ + size_ + count;

            // Move tail into new positions
            for (pointer p = old_end - 1; p >= pos_ptr; --p) {
                allocator_traits::construct(alloc_, std::addressof(*(p + count)), std::move_if_noexcept(*p));
                allocator_traits::destroy(alloc_, std::addressof(*p));
                if (p == pos_ptr) break;
            }

            pointer dest = pos_ptr;
            for (; first != last; ++first, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), *first);
            }

            size_ += count;
            return data_ + index;
        }
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_type index = static_cast<size_type>(pos - data_);
        if (index > size_) throw std::out_of_range("Vector::emplace");

        if (index == size_) {
            emplace_back(std::forward<Args>(args)...);
            return data_ + size_ - 1;
        }

        if (size_ == capacity_) {
            size_type new_cap = growth_capacity(size_ + 1);
            pointer new_data = allocate(new_cap);
            pointer dest = new_data;

            pointer src = data_;
            for (size_type i = 0; i < index; ++i, ++src, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            }

            allocator_traits::construct(alloc_, std::addressof(*dest), std::forward<Args>(args)...);
            pointer inserted = dest;
            ++dest;

            for (size_type i = index; i < size_; ++i, ++src, ++dest) {
                allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            }

            destroy_range(data_, data_ + size_);
            deallocate(data_, capacity_);

            data_ = new_data;
            capacity_ = new_cap;
            ++size_;
            return inserted;
        } else {
            pointer pos_ptr = data_ + index;
            allocator_traits::construct(alloc_, std::addressof(data_[size_]), std::move_if_noexcept(data_[size_ - 1]));
            for (size_type i = size_ - 1; i > index; --i) {
                data_[i] = std::move_if_noexcept(data_[i - 1]);
            }
            data_[index].~T();
            allocator_traits::construct(alloc_, std::addressof(*pos_ptr), std::forward<Args>(args)...);
            ++size_;
            return pos_ptr;
        }
    }

    iterator erase(const_iterator pos) {
        size_type index = static_cast<size_type>(pos - data_);
        if (index >= size_) throw std::out_of_range("Vector::erase");

        pointer pos_ptr = data_ + index;
        allocator_traits::destroy(alloc_, std::addressof(*pos_ptr));
        for (size_type i = index; i + 1 < size_; ++i) {
            allocator_traits::construct(alloc_, std::addressof(data_[i]), std::move_if_noexcept(data_[i + 1]));
            allocator_traits::destroy(alloc_, std::addressof(data_[i + 1]));
        }
        --size_;
        return data_ + index;
    }

    iterator erase(const_iterator first, const_iterator last) {
        size_type index_first = static_cast<size_type>(first - data_);
        size_type index_last  = static_cast<size_type>(last - data_);
        if (index_first > index_last || index_last > size_) {
            throw std::out_of_range("Vector::erase range");
        }

        if (index_first == index_last) return data_ + index_first;

        size_type count = index_last - index_first;
        pointer dest = data_ + index_first;
        pointer src  = data_ + index_last;

        for (size_type i = 0; i < count; ++i) {
            allocator_traits::destroy(alloc_, std::addressof(dest[i]));
        }

        for (; src != data_ + size_; ++dest, ++src) {
            allocator_traits::construct(alloc_, std::addressof(*dest), std::move_if_noexcept(*src));
            allocator_traits::destroy(alloc_, std::addressof(*src));
        }

        size_ -= count;
        return data_ + index_first;
    }

    void swap(Vector& other) noexcept(
        std::is_nothrow_swappable_v<allocator_type>) {
        using std::swap;
        if constexpr (allocator_traits::propagate_on_container_swap::value) {
            swap(alloc_, other.alloc_);
        }
        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }
};

// ------------------------------------------------------------
// Non-member operators
// ------------------------------------------------------------

template <typename T, typename Alloc>
bool operator==(const Vector<T, Alloc>& a,
                const Vector<T, Alloc>& b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i)
        if (!(a[i] == b[i])) return false;
    return true;
}

template <typename T, typename Alloc>
bool operator!=(const Vector<T, Alloc>& a,
                const Vector<T, Alloc>& b) {
    return !(a == b);
}

template <typename T, typename Alloc>
bool operator<(const Vector<T, Alloc>& a,
               const Vector<T, Alloc>& b) {
    return std::lexicographical_compare(
        a.begin(), a.end(),
        b.begin(), b.end()
    );
}

template <typename T, typename Alloc>
bool operator>(const Vector<T, Alloc>& a,
               const Vector<T, Alloc>& b) {
    return b < a;
}

template <typename T, typename Alloc>
bool operator<=(const Vector<T, Alloc>& a,
                const Vector<T, Alloc>& b) {
    return !(b < a);
}

template <typename T, typename Alloc>
bool operator>=(const Vector<T, Alloc>& a,
                const Vector<T, Alloc>& b) {
    return !(a < b);
}

template <typename T, typename Alloc>
void swap(Vector<T, Alloc>& a,
          Vector<T, Alloc>& b) noexcept(noexcept(a.swap(b))) {
    a.swap(b);
}
