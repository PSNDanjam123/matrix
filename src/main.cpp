#include <iostream>
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;

int main(void) {
    Matrix<char> m1;

    m1 = m1.convertList({'a', 'b'});

    std::cout << m1.str();

    return 0;
}
