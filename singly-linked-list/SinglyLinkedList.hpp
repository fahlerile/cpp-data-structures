#pragma once

// defining here because https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

template <typename LinkedList>
class LinkedListIterator
{
public:
    using ValueType = typename LinkedList::LinkedListNode;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

    LinkedListIterator(PointerType ptr) : m_ptr(ptr) {}

    LinkedListIterator& operator++()  // prefix
    {
        this->m_ptr = this->m_ptr->next;
        return *this;
    }

    LinkedListIterator& operator++(int)  // postfix
    {
        LinkedListIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    ReferenceType operator*()
    {
        return *(this->m_ptr);
    }

    bool operator==(const LinkedListIterator& other)
    {
        return this->m_ptr == other.m_ptr;
    }

    bool operator!=(const LinkedListIterator& other)
    {
        return this->m_ptr != other.m_ptr;
    }

private:
    PointerType m_ptr;
};

template <typename T>
class LinkedList
{
public:
    using Iterator = LinkedListIterator<LinkedList<T>>;

    struct LinkedListNode
    {
        T data;  // Data that node stores
        LinkedListNode *next;  // Pointer to a next node
    };

    LinkedList();  // Initialize an empty list
    LinkedList(std::initializer_list<T> items);  // Initialize the list with some values
    ~LinkedList();  // Free the heap allocated memory

    void push_back(T new_data);  // Add new data to the end of the list
    void prepend(T new_data);  // Add new data to the beginning of the list
    void insert(T new_data, int index);  // Add new data to specified index

    void pop_back();  // Delete last element
    void pop_beginning();  // Delete first element
    void delete_node(int index);  // Delete node at specified index

    int find(T data);  // Linear search over this linked list
    void swap(int idx_1, int idx_2);  // Swap data of two nodes

    void print();  // Pretty-print contents of a list
    int get_size();  // Get the size of a list

    T operator[](int index) const;  // Get data at specific index
    T& operator[](int index);  // Set data at specific index

    Iterator begin();
    Iterator end();

private:
    int size = 0;  // Size of the list
    LinkedListNode *root = nullptr;  // The root node of a list, its beginning
};

// Initialize an empty list
template <typename T>
LinkedList<T>::LinkedList() {}

// Initialize the list with some values
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> items)
{
    // backwards iterating over a init list and prepending to the beginning
    // (to not lose time traversing over a list each time we `push_back`)
    for (auto it = items.end() - 1, end = items.begin() - 1; it != end; it--)
        this->prepend(*it);
}

// Free the heap allocated memory
template <typename T>
LinkedList<T>::~LinkedList()
{
    auto *tmp = this->root;

    for (auto *p = this->root; p != nullptr; p = tmp)
    {
        tmp = p->next;
        delete p;
    }
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

// Add new data to specified index
template <typename T>
void LinkedList<T>::insert(T new_data, int index)
{
    if (index >= this->size || index < 0)
        throw std::invalid_argument("indexing out-of-bounds index for LinkedList<T>::insert method");

    LinkedListNode *new_node = new LinkedListNode;
    new_node->data = new_data;
    this->size++;

    if (index == 0)
    {
        new_node->next = this->root;
        this->root = new_node;
        return;
    }

    auto *p = this->root;
    // traverse over a linked list to a node before the one we need to insert
    for (int i = 0; i < (index - 1); i++, p = p->next);
    new_node->next = p->next;
    p->next = new_node;
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

// Delete first element
template <typename T>
void LinkedList<T>::pop_beginning()
{
    auto *tmp = this->root->next;
    delete this->root;
    this->root = tmp;
    this->size--;
}

// Delete node at specified index
template <typename T>
void LinkedList<T>::delete_node(int index)
{
    if (index >= this->size || index < 0)
        throw std::invalid_argument("indexing out-of-bounds index for LinkedList<T>::delete_node method");

    auto *p = this->root;
    // traverse until the next node is the one we need to delete
    for (int i = 0; i < (index - 1); i++, p = p->next);
    auto *tmp = p->next->next;
    delete p->next;
    p->next = tmp;
    this->size--;
}

// Linear search over this linked list
template <typename T>
int LinkedList<T>::find(T data)
{
    auto *p = this->root;
    for (int i = 0; p->next != nullptr; p = p->next, i++)
    {
        if (p->data == data)
            return i;
    }
    return -1;
}

// Swap data of two nodes
template <typename T>
void LinkedList<T>::swap(int idx1, int idx2)
{
    if (idx1 == idx2)
        return;

    // traverse to the node with index `idx1`
    auto *p1 = this->root;
    for (int i = 0; i < idx1; i++, p1 = p1->next);

    // traverse to the node with index `idx2`
    auto *p2 = this->root;
    for (int i = 0; i < idx2; i++, p2 = p2->next);

    auto tmp = p1->data;
    p1->data = p2->data;
    p2->data = tmp;
}

// Pretty-print contents of a list
template <typename T>
void LinkedList<T>::print()
{
    if (this->root == nullptr)
        return;

    for (auto item : *this)
        std::cout << item.data << " ";
    std::cout << std::endl;
}

// Get the size of a list
template <typename T>
int LinkedList<T>::get_size()
{
    return this->size;
}

// Get data at specific index
template <typename T>
T LinkedList<T>::operator[](int index) const
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

// Set data at specific index
template <typename T>
T& LinkedList<T>::operator[](int index)
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

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return LinkedListIterator<LinkedList<T>>(this->root);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return nullptr;  // because this should return the NEXT memory address after the last valid one
}
