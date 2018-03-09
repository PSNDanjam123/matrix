#include "./Jim/Core/Matrix.h"
#include <iostream>
using namespace Jim::Core;

int main(void) {
    Matrix<float> p(4,1);
    Matrix<float> m(4,4);

    m = m.identity();

    m.set(3,0, 2);

    p.set(0,0, 10)
        .set(1,0, 20)
        .set(2,0, 30);

    p = m * p;

    std::cout << m.str() << p.str();

    return 0;
}
