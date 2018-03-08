#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat<int> m1(3,2);
    Mat<int> m2(2,3);
    Mat<int> m3(2,2);

    m1(0,0) = 1;
    m1(1,0) = 2;
    m1(2,0) = 3;
    m1(0,1) = 4;
    m1(1,1) = 5;
    m1(2,1) = 6;

    m2(0,0) = 7;
    m2(1,0) = 8;
    m2(0,1) = 9;
    m2(1,1) = 10;
    m2(0,2) = 11;
    m2(1,2) = 12;

    m3 += m1 * m2;

    std::cout << m1.str() << '\n' << m2.str() << '\n' << m3.str();

    return 0;
}
