#pragma once
#include <stack>

template <typename BinarySearchTree>
class BinarySearchTreeIterator
{
public:
    using ValueType = typename BinarySearchTree::Node;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

    BinarySearchTreeIterator(PointerType ptr) : m_ptr(ptr) {}

    BinarySearchTreeIterator& operator++()  // prefix
    {
        // PRIORITY: LEFT -> RIGHT
        // the idea is to create a stack in which I am going to save pointers to the nodes I need to visit

        if (this->m_ptr->left != nullptr && this->m_ptr->right != nullptr)
        {
            this->visit_stack.push(this->m_ptr->right);
            this->m_ptr = this->m_ptr->left;
        }
        else if (this->m_ptr->left != nullptr && this->m_ptr->right == nullptr)
        {
            this->m_ptr = this->m_ptr->left;
        }
        else if (this->m_ptr->left == nullptr && this->m_ptr->right != nullptr)
        {
            this->m_ptr = this->m_ptr->right;
        }
        else if (this->m_ptr->left == nullptr && this->m_ptr->right == nullptr && this->visit_stack.empty())
        {
            this->m_ptr = nullptr;
        }
        else if (this->m_ptr->left == nullptr && this->m_ptr->right == nullptr)
        {
            this->m_ptr = this->visit_stack.top();
            this->visit_stack.pop();
        }
        return *this;
    }

    BinarySearchTreeIterator& operator++(int)  // postfix
    {
        BinarySearchTreeIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    ReferenceType operator*()
    {
        return *(this->m_ptr);
    }

    bool operator==(const BinarySearchTreeIterator& other)
    {
        return this->m_ptr == other.m_ptr;
    }

    bool operator!=(const BinarySearchTreeIterator& other)
    {
        return this->m_ptr != other.m_ptr;
    }

private:
    PointerType m_ptr;
    std::stack<PointerType> visit_stack;
};

// Binary search tree class. Template argument should be a number
// type (like int or float), or some other class/type with available
// comparison operators (<, >, ==, etc.)
template <typename T>
class BinarySearchTree
{
public:
    using Iterator = BinarySearchTreeIterator<BinarySearchTree<T>>;

    struct Node
    {
        Node *left = nullptr;
        Node *right = nullptr;
        T data;
    };

    BinarySearchTree();
    BinarySearchTree(std::initializer_list<T> items);

    void add(T new_data);  // Add new data
    bool search(T data);  // Search for specific data
    void delete_node(T data);  // Delete a node with specific value

    Iterator begin();
    Iterator end();

private:
    void add(T new_data, Node *&parent);  // Add new data to a specific subtree
    Node* search_node_return_pointer(T data, Node *parent);  // Search for a node with specific value and return a pointer to it

    Node *root = nullptr;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> items)
{
    for (T item : items)
        this->add(item);
}

template <typename T>
void BinarySearchTree<T>::add(T new_data)
{
    this->add(new_data, this->root);
}

template <typename T>
void BinarySearchTree<T>::add(T new_data, Node *&parent)
{
    if (parent == nullptr)
    {
        Node *new_node = new Node;
        new_node->data = new_data;
        parent = new_node;
        return;
    }

    if (new_data < parent->data)
        this->add(new_data, parent->left);
    else  // new_data >= parent->data
        this->add(new_data, parent->right);
}

template <typename T>
bool BinarySearchTree<T>::search(T data)
{
    return (this->search_node_return_pointer(data, this->root) != nullptr);
}

template <typename T>
void BinarySearchTree<T>::delete_node(T data)
{
    Node *node_to_delete = this->search_node_return_pointer(data, this->root);
    if (node_to_delete == nullptr)
        return;

    // if is a leaf node
    if (node_to_delete->left == nullptr && node_to_delete->right == nullptr)
    {
        // delete this node (free the memory, set a pointer to it in parent to nullptr)
    }
    // else (if it has children)
        // traverse over this subtree, adding every child's value to a std::vector<T>
        // delete this node (free the memory for it and all of its children, set a pointer to it in parent to nullptr)
        // call this->add for every of children' values (they are in std::vector<T>)
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::search_node_return_pointer(T data, Node *parent)
{
    if (parent->data == data)
        return parent;

    if (parent->data > data)
    {
        if (parent->left == nullptr)
            return nullptr;
        return this->search_node_return_pointer(data, parent->left);
    }
    else  // parent->data <= data
    {
        if (parent->right == nullptr)
            return nullptr;
        return this->search_node_return_pointer(data, parent->right);
    }
}

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin()
{
    return Iterator(this->root);
}

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::end()
{
    return Iterator(nullptr);
}