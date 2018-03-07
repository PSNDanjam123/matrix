#include <iostream>
#include "./Jim/Matrix/Mat4.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> example;

    int t = 2;
    float a = example.get(1,1);
    example.map([t](float val) { return val + t;});
    float b = example.get(1,1);
    float c = example.get(1,2);

    std::cout << a << ' ' << b << ' ' << c << '\n';

    return 0;
}
