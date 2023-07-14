#include <iostream>
#include "Vector.hpp"

int main()
{
    std::cout << "Hello, vector!" << std::endl;

    Vector<int> vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector.print();
    std::cout << vector.get_size() << std::endl;
}