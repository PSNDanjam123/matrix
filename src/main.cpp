#include "./Jim/Core/Matrix.h"
#include <iostream>
using namespace Jim::Core;

int main(void) {
    Matrix<float> m1(3,2);
    Matrix<int> m2(2,3);
    Matrix<float> m3(2,2);

    m1.set(0, 0, 1)
        .set(1, 0, 2)
        .set(2, 0, 3)
        .set(0, 1, 4)
        .set(1, 1, 5)
        .set(2, 1, 6);

    m2.set(0, 0, 7)
        .set(1, 0, 8)
        .set(0, 1, 9)
        .set(1, 1, 10)
        .set(0, 2, 11)
        .set(1, 2, 12);

    m3 = m1 * m2;

    std::cout << m1.str() << '\n' << m2.str() << '\n' << m3.str();

    return 0;
}
