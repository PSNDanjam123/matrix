#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> a;
    Mat4<float> b;

    a += 2;
    b += 3;

    Mat4<float> c = a + b + b + a;

    std::cout << c.str();

    return 0;
}
