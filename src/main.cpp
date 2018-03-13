#include <iostream>
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;

int main(void) {
    Matrix<int> m1(4,4);
    m1 = m1.identity();

    m1 *= 2;

    m1 *= {{1},{2},{3},{1}};

    std::cout << m1.str();

    return 0;
}
