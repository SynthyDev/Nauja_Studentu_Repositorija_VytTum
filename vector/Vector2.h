#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <utility>
#include <limits>
#include <string>

template<typename T, typename Allocator = std::allocator<T>>
class Vector
{
public:
    using value_type             = T;
    using allocator_type         = Allocator;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;

    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    allocator_type _alloc;
    pointer _data;
    size_type _size;
    size_type _capacity;

private:

    void destroy_elements()
    {
        for (size_type i = 0; i < _size; ++i)
            std::allocator_traits<Allocator>::destroy(_alloc, _data + i);

        _size = 0;
    }

    void deallocate_storage()
    {
        if (_data)
        {
            std::allocator_traits<Allocator>::deallocate(
                _alloc,
                _data,
                _capacity
            );
        }

        _data = nullptr;
        _capacity = 0;
    }

    void reallocate(size_type new_capacity)
    {
        pointer new_data =
            std::allocator_traits<Allocator>::allocate(_alloc, new_capacity);

        size_type constructed = 0;

        try
        {
            for (; constructed < _size; ++constructed)
            {
                std::allocator_traits<Allocator>::construct(
                    _alloc,
                    new_data + constructed,
                    std::move_if_noexcept(_data[constructed])
                );
            }
        }
        catch (...)
        {
            for (size_type i = 0; i < constructed; ++i)
            {
                std::allocator_traits<Allocator>::destroy(
                    _alloc,
                    new_data + i
                );
            }

            std::allocator_traits<Allocator>::deallocate(
                _alloc,
                new_data,
                new_capacity
            );

            throw;
        }

        destroy_elements();
        deallocate_storage();

        _data = new_data;
        _capacity = new_capacity;
        _size = constructed;
    }

    void grow_if_needed()
    {
        if (_size >= _capacity)
        {
            size_type new_capacity = (_capacity == 0) ? 1 : (_capacity * 2);
            reallocate(new_capacity);
        }
    }

public:

    /* ============================================================
                            Constructors
       ============================================================ */

    Vector()
        : _data(nullptr),
          _size(0),
          _capacity(0)
    {
    }

    explicit Vector(size_type count)
        : Vector()
    {
        resize(count);
    }

    Vector(size_type count, const T& value)
        : Vector()
    {
        reserve(count);

        for (size_type i = 0; i < count; ++i)
            push_back(value);
    }

    Vector(std::initializer_list<T> init)
        : Vector()
    {
        reserve(init.size());

        for (const auto& value : init)
            push_back(value);
    }

    Vector(const Vector& other)
        : Vector()
    {
        reserve(other._size);

        for (const auto& value : other)
            push_back(value);
    }

    Vector(Vector&& other) noexcept
        : _alloc(std::move(other._alloc)),
          _data(other._data),
          _size(other._size),
          _capacity(other._capacity)
    {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    ~Vector()
    {
        destroy_elements();
        deallocate_storage();
    }

    /* ============================================================
                            Assignment
       ============================================================ */

    Vector& operator=(const Vector& other)
    {
        if (this == &other)
            return *this;

        Vector temp(other);
        swap(temp);

        return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if (this == &other)
            return *this;

        destroy_elements();
        deallocate_storage();

        _alloc = std::move(other._alloc);
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;

        return *this;
    }

    /* ============================================================
                            Iterators
       ============================================================ */

    iterator begin() noexcept { return _data; }
    const_iterator begin() const noexcept { return _data; }

    const_iterator cbegin() const noexcept { return _data; }

    iterator end() noexcept { return _data + _size; }
    const_iterator end() const noexcept { return _data + _size; }

    const_iterator cend() const noexcept { return _data + _size; }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    /* ============================================================
                            Capacity
       ============================================================ */

    bool empty() const noexcept
    {
        return _size == 0;
    }

    size_type size() const noexcept
    {
        return _size;
    }

    size_type capacity() const noexcept
    {
        return _capacity;
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    void reserve(size_type new_capacity)
    {
        if (new_capacity > _capacity)
            reallocate(new_capacity);
    }

    void shrink_to_fit()
    {
        if (_size < _capacity)
            reallocate(_size);
    }

    void resize(size_type count)
    {
        resize(count, T());
    }

    void resize(size_type count, const T& value)
    {
        if (count < _size)
        {
            for (size_type i = count; i < _size; ++i)
            {
                std::allocator_traits<Allocator>::destroy(
                    _alloc,
                    _data + i
                );
            }

            _size = count;
        }
        else if (count > _size)
        {
            reserve(count);

            while (_size < count)
                push_back(value);
        }
    }

    /* ============================================================
                            Element Access
       ============================================================ */

    reference operator[](size_type index)
    {
        return _data[index];
    }

    const_reference operator[](size_type index) const
    {
        return _data[index];
    }

    reference at(size_type index)
    {
        if (index >= _size)
            throw std::out_of_range("Vector::at");

        return _data[index];
    }

    const_reference at(size_type index) const
    {
        if (index >= _size)
            throw std::out_of_range("Vector::at");

        return _data[index];
    }

    reference front()
    {
        return _data[0];
    }

    const_reference front() const
    {
        return _data[0];
    }

    reference back()
    {
        return _data[_size - 1];
    }

    const_reference back() const
    {
        return _data[_size - 1];
    }

    pointer data() noexcept
    {
        return _data;
    }

    const_pointer data() const noexcept
    {
        return _data;
    }

    /* ============================================================
                            Modifiers
       ============================================================ */

    void clear() noexcept
    {
        destroy_elements();
    }

    void push_back(const T& value)
    {
        grow_if_needed();

        std::allocator_traits<Allocator>::construct(
            _alloc,
            _data + _size,
            value
        );

        ++_size;
    }

    void push_back(T&& value)
    {
        grow_if_needed();

        std::allocator_traits<Allocator>::construct(
            _alloc,
            _data + _size,
            std::move(value)
        );

        ++_size;
    }

    template<typename... Args>
    reference emplace_back(Args&&... args)
    {
        grow_if_needed();

        std::allocator_traits<Allocator>::construct(
            _alloc,
            _data + _size,
            std::forward<Args>(args)...
        );

        ++_size;

        return back();
    }

    void pop_back()
    {
        if (_size == 0)
            return;

        --_size;

        std::allocator_traits<Allocator>::destroy(
            _alloc,
            _data + _size
        );
    }

    iterator insert(iterator pos, const T& value)
    {
        size_type index = pos - begin();

        grow_if_needed();

        pos = begin() + index;

        for (iterator it = end(); it != pos; --it)
        {
            std::allocator_traits<Allocator>::construct(
                _alloc,
                it,
                std::move(*(it - 1))
            );

            std::allocator_traits<Allocator>::destroy(
                _alloc,
                it - 1
            );
        }

        std::allocator_traits<Allocator>::construct(
            _alloc,
            pos,
            value
        );

        ++_size;

        return pos;
    }

    iterator erase(iterator pos)
    {
        size_type index = pos - begin();

        // shift elements left with destroy+construct to keep destructors correct
        for (size_type i = index; i < _size - 1; ++i)
        {
            std::allocator_traits<Allocator>::destroy(_alloc, _data + i);
            std::allocator_traits<Allocator>::construct(
                _alloc,
                _data + i,
                std::move(_data[i + 1])
            );
        }

        pop_back(); // destroys last element and decrements _size
        return begin() + index;
    }
    void swap(Vector& other) noexcept
    {
        std::swap(_alloc, other._alloc);
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    /* ============================================================
                            Comparison
       ============================================================ */

    bool operator==(const Vector& other) const
    {
        if (_size != other._size)
            return false;

        for (size_type i = 0; i < _size; ++i)
        {
            if (!(_data[i] == other._data[i]))
                return false;
        }

        return true;
    }

    bool operator!=(const Vector& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const
    {
        return std::lexicographical_compare(
            begin(),
            end(),
            other.begin(),
            other.end()
        );
    }

    bool operator>(const Vector& other) const
    {
        return other < *this;
    }

    bool operator<=(const Vector& other) const
    {
        return !(other < *this);
    }

    bool operator>=(const Vector& other) const
    {
        return !(*this < other);
    }

iterator erase(iterator first, iterator last)
{
    if (first == last) return first;

    size_type index = first - begin();
    size_type count = last - first;

    // shift tail left
    for (size_type i = index; i + count < _size; ++i)
    {
        std::allocator_traits<Allocator>::destroy(_alloc, _data + i);
        std::allocator_traits<Allocator>::construct(
            _alloc,
            _data + i,
            std::move(_data[i + count])
        );
    }

    // destroy trailing elements
    for (size_type i = 0; i < count; ++i)
        pop_back();

    return begin() + index;
    }
};