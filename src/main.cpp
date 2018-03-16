#include "./Jim/Component/Core/Object.h"

#include <iostream>

using namespace Jim::Component::Core;
using namespace Jim::Core::Types;

int main(void) {
    Object test;

    test.setVertexBuffer({
            -1,-1, 0,
            -1, 1, 0,
             1, 1, 0});

    matrix m = test.getMatrix();

    std::cout << m.str();

    return 0;
}
