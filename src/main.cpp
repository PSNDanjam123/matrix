#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> a;
    Mat4<float> b;
    Mat4<float> c;

    a += 2;
    b += 3;
    c += 2;

    Mat4<float> d = a + b + 11 + b + a;
    Mat4<float> e = a.identity() + 1;

    std::cout << a.str() << b.str() << c.str() << d.str() << e.str();

    if(a == b) {
        std::cout << "a == b\n";
    } else if(a != b) {
        std::cout << "a != b\n";
    }

    if(a == c) {
        std::cout << "a == c\n";
    } else if(a != c) {
        std::cout << "a != c\n";
    }

    return 0;
}
