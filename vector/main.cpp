#include <iostream>
#include "Vector.hpp"

int main()
{
    std::cout << "Hello, vector!" << std::endl;

    Vector<int> vector {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector.insert(727, 0);
    vector.print();
}