#pragma once

// defining here because https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

template <typename T>
struct LinkedListNode
{
    T data;  // Data that node stores
    LinkedListNode *next;  // Pointer to a next node
};

template <typename T>
class LinkedList
{
private:
    int size;  // Size of the list
    LinkedListNode<T> *root;  // The root node of a list, its beginning

public:
    LinkedList();
    LinkedList(std::initializer_list<T> items);

    void push_back(T new_data);  // Adds new data to the end of the list
    void insert();  // Add new data to specified index

    void pop_back();  // Delete last element

    void print();  // Pretty-print contents of a list
    int get_size();  // Get the size of a list

    T operator[](int index);  // Get data at specific index
};

// Initializes an empty list
template <typename T>
LinkedList<T>::LinkedList()
{
    this->root = nullptr;
    this->size = 0;
}

// Initializes a list with some initial values
// TODO: replace this with backwards iterating over a init list and prepending to the root
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> items)
{
    this->root = nullptr;
    this->size = 0;
    for (T item : items)
        this->push_back(item);
}

// Add new data to the end of the list
template <typename T>
void LinkedList<T>::push_back(T new_data)
{
    LinkedListNode<T> *new_node = new LinkedListNode<T>;
    new_node->data = new_data;
    new_node->next = nullptr;

    if (this->root == nullptr)
    {
        this->root = new_node;
    }
    else
    {
        auto *p = this->root;
        for (; p->next != nullptr; p = p->next);
        p->next = new_node;
    }

    this->size++;
}

// Add new data to specified index
// TODO: create this
template <typename T>
void LinkedList<T>::insert()
{

}

// Delete last element
template <typename T>
void LinkedList<T>::pop_back()
{
    auto *p = this->root;
    // traverse until the next node of a next node is a null pointer (so `p` is second to last node)
    for (; (p->next)->next != nullptr; p = p->next);

    delete (p->next);  // free the heap allocated memory
    p->next = nullptr;  // remove the pointer to this freed memory (to last node)

    this->size--;
}

// Pretty-print contents of a list
template <typename T>
void LinkedList<T>::print()
{
    if (this->root == nullptr)
        return;

    for (auto *p = this->root; p != nullptr; p = p->next)
    {
        std::cout << p->data << " ";
    }
    std::cout << std::endl;
}

// Get the size of a list
template <typename T>
int LinkedList<T>::get_size()
{
    return this->size;
}

template <typename T>
T LinkedList<T>::operator[](int index)
{
    if (index >= this->size)
    {
        throw std::invalid_argument("indexing out-of-bounds index with brackets operator");
    }
    if (index < 0)
    {
        index = this->size + index;
    }

    auto *p = this->root;
    for (int i = 0; i < index; i++, p = p->next);
    return p->data;
}
