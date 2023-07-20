#include <iostream>
#include "BinarySearchTree.hpp"

int main()
{
    std::cout << "Hello, binary search tree!" << std::endl;
    BinarySearchTree<int> tree {7, 3, 5, 1, 10, 17, 23, 727, 1488, 1337, 98, 42, -50, -10};

    std::cout << "23 in tree: " << tree.search(23) << std::endl;
    std::cout << "1 in tree: " << tree.search(1) << std::endl;
    std::cout << "727 in tree: " << tree.search(727) << std::endl;

    for (auto item : tree)
    {
        std::cout << item.data << std::endl;
    }
}