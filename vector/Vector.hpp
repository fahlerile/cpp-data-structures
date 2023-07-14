#pragma once

// Using `malloc` and `free` instead of `new` and `delete` because I need to use `std::realloc`
// (valgrind notifies about "free() delete delete[] mismatch")

template <typename T>
class Vector
{
public:
    Vector();  // Initialize a vector with no elements
    Vector(std::initializer_list<T> items);  // Initialize a vector with some elements in it
    ~Vector();  // Delete a vector, free the memory

    void push_back(T new_data);  // Add new data to the end of element

    void pop_back();  // Delete a last element

    void print();  // Pretty-print a vector
    int get_size();  // Get the size of a vector

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

// Reallocate memory if it is not enough
template <typename T>
void Vector<T>::reallocate_memory()
{
    T *tmp = (T*) std::realloc(this->data, sizeof(T) * (this->size + this->size_increment));
    this->allocated += this->size_increment;
    this->data = tmp;
}
