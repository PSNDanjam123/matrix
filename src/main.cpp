#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat<int> m1(2,3);
    Mat<float> m2(2,3);
    Mat4<float> m5;
    Mat<int> m7(4,4);
    m7.map([](float, unsigned, unsigned) {return 3;});

    m1.map([](float) {
            return 2;
            });

    std::cout << m1.str() << "\n\n";

    int m = 5;
    m2.map([&m](float, unsigned x, unsigned y) {return (x + y) * m;});

    m1 += m2;

    m1 += 2;

    Mat<int> m3 = m1.clone();

    m5(0,0) = 666;

    Mat4<float> m6 = m5.clone();

    m5(0,0) = 10;
    m6(1,2) = 45;

    m6 += m7;

    std::cout << m1.str() << "\n\n";

    std::cout << m3.str() << "\n\n";

    std::cout << m5.str() << "\n\n";

    std::cout << m6.str() << "\n\n";

    std::cout << m7.str() << "\n\n";

    return 0;
}
