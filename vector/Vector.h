template <typename T>
class MyVector {
private:
    T* arr;        // Pointer to dynamically allocated array
    size_t size;   // Number of elements in the vector
    size_t capacity; // Capacity of the vector

    void resize(); // Utility function to handle resizing

public:
    MyVector();                 // Default constructor
    ~MyVector();                // Destructor

    MyVector(const MyVector& other);        // Copy constructor
    MyVector& operator=(const MyVector& other); // Copy assignment operator

    MyVector(MyVector&& other) noexcept;        // Move constructor
    MyVector& operator=(MyVector&& other) noexcept; // Move assignment operator

    void push_back(const T& element); // Add element
    void pop_back(); // Remove last element

    size_t get_size() const;
    size_t get_capacity() const;

    T& operator[](size_t index);
};