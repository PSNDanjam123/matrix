#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4f m1;


    m1 += 4 * m1.identity();

    std::cout << m1.str();

    return 0;
}
