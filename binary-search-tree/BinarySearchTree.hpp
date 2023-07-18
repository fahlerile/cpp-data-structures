#pragma once

// Binary search tree class. Template argument should be a number
// type (like int or float), or some other class/type with available
// comparison operators (<, >, ==, etc.)
template <typename T>
class BinarySearchTree
{
public:
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

private:
    void add(T new_data, Node *&parent);
    Node* search_node_return_pointer(T data, Node *parent);

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
