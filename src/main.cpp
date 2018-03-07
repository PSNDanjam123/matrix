#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> m4;
    Mat<int> m(2,3);

    int t = 1;

    m.map([](float, unsigned x, unsigned y) {
            return x + y;
            }).map([&t](float val, unsigned, unsigned) {
                return val + t++;
                });

    std::cout << m.str();

    return 0;
}
