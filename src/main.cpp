#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> a;
    Mat4<float> b;
    Mat4<int> c;

    a += 3;
    b += 4;
    c += 1;

    if(a != c) {
        std::cout << "works";
    }

    return 0;
}
