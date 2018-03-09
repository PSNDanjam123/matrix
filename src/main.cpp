#include "./Jim/Core/Matrix.h"
#include <iostream>
using namespace Jim::Core;

int main(void) {
    Matrix<float> m(4,4);

    m.resize(3,3).resize(2,2);

    std::cout << m.identity().str();

    return 0;
}
