#include <iostream>
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;

int main(void) {
    Matrix<int> m1(4,4);
    Matrix<float> m2(1,4);

    std::cout << m1.str();

    return 0;
}
