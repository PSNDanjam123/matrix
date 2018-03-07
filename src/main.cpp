#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> m4;
    Mat<int> m(2,3);

    m.map([](float, unsigned x, unsigned y) {
            return x + y;
            });

    std::cout << m.str();

    return 0;
}
