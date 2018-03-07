#include <iostream>
#include "./Jim/Matrix/Mat4.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> m;
    int multiplyer = 4;
    m.map([multiplyer](float, unsigned x, unsigned y) {return (x + y) * multiplyer;});

    m(2,2) = m(1,1) + m(1,3);

    std::cout << m.str();

    return 0;
}
