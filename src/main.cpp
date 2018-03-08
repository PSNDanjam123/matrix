#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat<int> m1(3,2);
    Mat<int> m2(2,3);
    Mat<int> m3(3,2);

    m1(0,0) = 1;
    m1(1,0) = 2;
    m1(2,0) = 3;
    m1(0,1) = 4;
    m1(1,1) = 5;
    m1(2,1) = 6;

    m3 += m1.clone() + m1.clone();

    std::cout << m3.str();

    return 0;
}
