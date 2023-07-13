#include <iostream>
#include "LinkedList.hpp"

int main()
{
    LinkedList<int> list {8, 1, 2, 7, 7, 2, 1, 0, 6};  // initializing linked list with some values
    std::cout << "Hello, linked list!" << std::endl;
    std::cout << "Before: ";
    list.print();
    std::cout << "Size: " << list.get_size() << std::endl;

    // for (auto item : list)
    // {
    //     std::cout << item << " ";
    // }
    // std::cout << std::endl;

    std::cout << list[-2] << " is at index -2" << std::endl;
    std::cout << list[3] << " is at index 3" << std::endl;

    list.pop_back();
    list.prepend(1);

    list[0] = 92;

    std::cout << "After: ";
    list.print();
    std::cout << "Size: " << list.get_size() << std::endl;
}