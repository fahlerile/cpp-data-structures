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
        this->temp = *this;
        ++(*this);
        return this->temp;
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

    PointerType get_pointer()
    {
        return m_ptr;
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
    Node* search_node_return_pointer(T data);  // Search for a node with specific value and return a pointer to it
std::pair<BinarySearchTree<T>::Node*, BinarySearchTree<T>::Node*> search_node_return_parent_and_pointer(T data, Node *root, Node *parent);  // Search for a node, return (parent_pointer, node_pointer). ALWAYS CALL WITH parent = NULLPTR!!!

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
    return (this->search_node_return_pointer(data) != nullptr);
}

template <typename T>
void BinarySearchTree<T>::delete_node(T data)
{
    std::pair<Node*, Node*> node_pair = this->search_node_return_parent_and_pointer(data, this->root, nullptr);

    Node* parent_node = node_pair.first;
    Node* node_to_delete = node_pair.second;

    if (parent_node == nullptr && node_to_delete == nullptr)  // if did not find this node
        return;

    // if is a leaf node
    if (node_to_delete->left == nullptr && node_to_delete->right == nullptr)
    {
        // delete this node (free the memory, set a pointer to it in parent to nullptr)
        if (parent_node->left == node_to_delete)
            parent_node->left = nullptr;
        else if (parent_node->right == node_to_delete)
            parent_node->right = nullptr;
        delete node_to_delete;
    }
    // else (if it has children)
    else
    {
        // traverse over this subtree, adding every child's value to a std::vector<T>
        // delete this node (free the memory for it and all of its children, set a pointer to it in parent to nullptr)
        // call this->add for every of children' values (they are in std::vector<T>)
    }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::search_node_return_pointer(T data)
{
    for (auto it = this->begin(), end = this->end(); it != end; ++it)
    {
        if ((*it).data == data)
            return it.get_pointer();
    }
    return nullptr;
}

template <typename T>
std::pair<BinarySearchTree<T>::Node*, BinarySearchTree<T>::Node*> BinarySearchTree<T>::search_node_return_parent_and_pointer(T data, Node *root, Node *parent)
{
    if (root->data == data)
        return std::pair<BinarySearchTree<T>::Node*, BinarySearchTree<T>::Node*> {parent, root};

    if (root->data > data)
    {
        if (root->left == nullptr)
            return std::pair<BinarySearchTree<T>::Node*, BinarySearchTree<T>::Node*> {nullptr, nullptr};
        return this->search_node_return_parent_and_pointer(data, root->left, root);
    }
    else  // root->data <= data
    {
        if (root->right == nullptr)
            return std::pair<BinarySearchTree<T>::Node*, BinarySearchTree<T>::Node*> {nullptr, nullptr};
        return this->search_node_return_parent_and_pointer(data, root->right, root);
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