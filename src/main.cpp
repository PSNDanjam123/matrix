#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4l m1;
    Mat4l m2;
    Matl m3(4,4);

    m1 += m2.identity();
    m1 += m3.identity();

    std::cout << m1.str();

    return 0;
}
