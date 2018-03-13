#include <iostream>
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;

int main(void) {
    Matrix<int> m1(4,4);
    Matrix<float> m2(1,4);

    m1 = m1.identity();

    m2.set(0,0,1).set(0,1,2).set(0,2,3).set(0,3,1);

    m1 = m2;

    std::cout << m1.str();

    return 0;
}
