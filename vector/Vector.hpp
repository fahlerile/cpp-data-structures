#pragma once
#include <cstring>

// Using `malloc` and `free` instead of `new` and `delete` because I need to use `std::realloc`
// (valgrind notifies about "free() delete delete[] mismatch")

template <typename Vector>
class VectorIterator
{
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

    VectorIterator(PointerType ptr) : m_ptr(ptr) {}

    VectorIterator& operator++()  // prefix
    {
        this->m_ptr++;
        return *this;
    }

    VectorIterator& operator++(int)  // postfix
    {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    ReferenceType operator*()
    {
        return *(this->m_ptr);
    }

    bool operator==(const VectorIterator& other)
    {
        return this->m_ptr == other.m_ptr;
    }

    bool operator!=(const VectorIterator& other)
    {
        return this->m_ptr != other.m_ptr;
    }


private:
    PointerType m_ptr;
};

template <typename T>
class Vector
{
public:
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;

    Vector();  // Initialize a vector with no elements
    Vector(std::initializer_list<T> items);  // Initialize a vector with some elements in it
    ~Vector();  // Delete a vector, free the memory

    void push_back(T new_data);  // Add new data to the end of element
    void prepend(T new_data);  // Add new data to the beginning
    void insert(T new_data, int index);  // Add new data at the specific index

    void pop_back();  // Delete a last element
    void pop_beginning();  // Delete first element
    void delete_at_index(int index);  // Delete element at a specific index

    void print();  // Pretty-print a vector
    int get_size();  // Get the size of a vector

    T operator[](int index) const;  // Get data at specific index
    T& operator[](int index);  // Set data at specific index

    Iterator begin();
    Iterator end();

private:
    int allocated = 5;  // For how many elements the memory is allocated currently (max `size`)
    int size = 0;  // Size of vector
    const int size_increment = 5;
    T *data = (T*) malloc(sizeof(T) * this->allocated);  // Pointer to an array of stored data

    void reallocate_memory();  // Reallocate memory if it is not enough
};

// Initialize a vector with no elements
template <typename T>
Vector<T>::Vector() {}

// Initialize a vector with some elements in it
template <typename T>
Vector<T>::Vector(std::initializer_list<T> items)
{
    for (auto item : items)
        this->push_back(item);
}

// Delete a vector, free the memory
template <typename T>
Vector<T>::~Vector()
{
    free(this->data);
}

// Add new data to the end of element
template <typename T>
void Vector<T>::push_back(T new_data)
{
    if (this->size == allocated)
        this->reallocate_memory();

    this->data[this->size] = new_data;
    this->size++;
}

// Add new data to the beginning
template <typename T>
void Vector<T>::prepend(T new_data)
{
    this->insert(new_data, 0);
}

// Add new data at the specific index
template <typename T>
void Vector<T>::insert(T new_data, int index)
{
    if (this->size == allocated)
        this->reallocate_memory();

    std::memcpy(&(this->data[index]) + 1, &this->data[index], (this->size - index) * sizeof(T));
    this->data[index] = new_data;
    this->size++;
}

// Delete a last element
template <typename T>
void Vector<T>::pop_back()
{
    if (this->size <= 0)
        throw std::length_error("trying to delete last element from the list with size = 0 (Vector::pop_back)");
    this->size--;
}

// Pretty-print a vector
template <typename T>
void Vector<T>::print()
{
    for (int i = 0; i < this->size; i++)
        std::cout << this->data[i] << " ";
    std::cout << std::endl;
}

// Get the size of a vector
template <typename T>
int Vector<T>::get_size()
{
    return this->size;
}

// Get data at specific index
template <typename T>
T Vector<T>::operator[](int index) const
{
    return this->data[index];
}

// Set data at specific index
template <typename T>
T& Vector<T>::operator[](int index)
{
    return this->data[index];
}

// Reallocate memory if it is not enough
template <typename T>
void Vector<T>::reallocate_memory()
{
    T *tmp = (T*) std::realloc(this->data, sizeof(T) * (this->size + this->size_increment));
    this->allocated += this->size_increment;
    this->data = tmp;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    return VectorIterator<Vector<T>>(this->data);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
    return VectorIterator<Vector<T>>(this->data + this->size);
}
