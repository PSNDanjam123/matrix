#include <iostream>
#include "./Jim/Matrix/Mat4.h"
using namespace Jim::Matrix;

int main(void) {
    Mat4<float> m;
    int multiplyer = 4;
    m.map([multiplyer](float, unsigned x, unsigned y) {return (x + y) * multiplyer;});

    m(2,2) = m(1,1) + m(1,3);

    for(unsigned x = 0; x < 4; x++) {
        for(unsigned y = 0; y < 4; y++) {
            std::cout << m(x,y) << '\t';
            if(y == 3) {
                std::cout << '\n';
            }
        }
    }

    return 0;
}
