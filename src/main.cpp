#include "./Jim/Core/Matrix.h"
#include <iostream>
using namespace Jim::Core;

int main(void) {
    Matrix<float> p(1,4);
    Matrix<float> m(4,4);

    m = m.identity();

    m.set(3,0, 5);

    p.set(0,0, 10)
        .set(0,1, 20)
        .set(0,2, 30)
        .set(0,3, 1);

    p = m * p;

    std::cout << m.str() << p.str();

    return 0;
}
