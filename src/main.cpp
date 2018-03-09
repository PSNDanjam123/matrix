#include "./Jim/Core/Matrix.h"
#include <iostream>
#include <cmath>
using namespace Jim::Core;

#define PI 3.14159265

int main(void) {
    //Triangle
    Matrix<float> p1(4,1);
    Matrix<float> p2(4,1);
    Matrix<float> p3(4,1);

               //x          //y
    p1.set(0,0,  1).set(1,0, -1);
    p2.set(0,0,  0).set(1,0,  1);
    p3.set(0,0, -1).set(1,0, -1);

    //4x4 Matrix
    Matrix<int> m(4,4);
    m = m.identity();

    int deg = 90;

    //Rotate around Z
    m.set(0,0, std::cos(deg*PI/180));
    m.set(1,0, -std::sin(deg*PI/180));
    m.set(0,1, std::sin(deg*PI/180));
    m.set(1,1, std::cos(deg*PI/180));

    std::cout << p1.str() << p2.str() << p3.str() << '\n';

    p1 = p1 * m;
    p2 = p2 * m;
    p3 = p3 * m;

    std::cout << p1.str() << p2.str() << p3.str() << '\n';

    return 0;
}
