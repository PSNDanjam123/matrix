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

    std::cout << a.str() << '\n';
    std::cout << b.str() << '\n';
    std::cout << c.str() << '\n';

    a -= c;

    a -= 4;

    std::cout << a.str() << '\n';

    return 0;
}
