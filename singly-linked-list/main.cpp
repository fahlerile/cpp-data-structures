#include <iostream>
#include "SinglyLinkedList.hpp"

int main()
{
    LinkedList<int> list {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // initializing linked list with some values
    std::cout << "Hello, linked list!" << std::endl;
    std::cout << "Before: ";
    list.print();
    std::cout << "Size: " << list.get_size() << std::endl;

    list.swap(0, 7);

    list.print();
}