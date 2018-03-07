#include <iostream>
#include "./Jim/Matrix/Mat4.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> example;

    example.test().transform().test().transform();

    return 0;
}
