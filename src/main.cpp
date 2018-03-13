#include <iostream>
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;

int main(void) {
    Matrix<int> m1 = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };

    Matrix<float> m2 = {{1.1},{3.0},{4.0},{6.5}};

    Matrix<float> m3 = (Matrix<float>)m1 * m2;

    std::cout << m3.str();

    return 0;
}
