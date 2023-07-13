#pragma once

// defining here because https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

// template <typename T>
// struct LinkedListNode
// {
//     T data;  // Data that node stores
//     LinkedListNode *next;  // Pointer to a next node
// };

template <typename T>
class LinkedList
{
private:
    struct LinkedListNode
    {
        T data;  // Data that node stores
        LinkedListNode *next;  // Pointer to a next node
    };

    int size = 0;  // Size of the list
    LinkedListNode *root = nullptr;  // The root node of a list, its beginning

public:
    LinkedList();
    LinkedList(std::initializer_list<T> items);

    void push_back(T new_data);  // Add new data to the end of the list
    void insert();  // Add new data to specified index
    void prepend(T new_data);  // Add new data to the beginning of the list

    void pop_back();  // Delete last element

    void print();  // Pretty-print contents of a list
    int get_size();  // Get the size of a list

    T operator[](int index);  // Get data at specific index
};

// Initializes an empty list
template <typename T>
LinkedList<T>::LinkedList() {}

// Initializes a list with some initial values
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> items)
{
    // backwards iterating over a init list and prepending to the beginning
    // (to not lose time traversing over a list each time we push_back)
    for (auto it = items.end() - 1, end = items.begin() - 1; it != end; it--)
        this->prepend(*it);
}

// Add new data to the end of the list
template <typename T>
void LinkedList<T>::push_back(T new_data)
{
    LinkedListNode *new_node = new LinkedListNode;
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

// Add new data to the beginning of the list
template <typename T>
void LinkedList<T>::prepend(T new_data)
{
    LinkedListNode *new_node = new LinkedListNode;
    new_node->data = new_data;
    new_node->next = this->root;
    this->root = new_node;
    this->size++;
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
    if (index >= this->size || index <= -this->size)
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
