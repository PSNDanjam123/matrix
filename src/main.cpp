#include <iostream>
#include "./Jim/Matrix.h"
using namespace Jim::Matrix;

int main(void) {
    Mat<int> m1(2,3);
    Mat<float> m2(2,3);

    m1.map([](float) {
            return 2;
            });

    std::cout << m1.str() << "\n\n";

    int m = 5;
    m2.map([&m](float, unsigned x, unsigned y) {return (x + y) * m;});

    m1 += m2;

    m1 += 2;

    std::cout << m1.str() << "\n\n";

    return 0;
}
