#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4f m;

    m.translate(50, 20, 10) += m.identity();

    std::cout << m.str();

    return 0;
}
