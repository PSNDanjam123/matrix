#include "./Jim/Core/Object.h"
using namespace Jim::Core;

int main(void) {
    Object cube = {
        //Front
        -1, -1,  1,
        -1,  1,  1,
        1,  1,  1,
        1, -1,  1,

        //Back
        -1, -1, -1,
        -1,  1, -1,
        1,  1, -1,
        1, -1, -1,

        //Left
        -1, -1,  1,
        -1,  1,  1,
        -1, -1, -1,
        -1,  1, -1,

        //Right
        1, -1,  1,
        1,  1,  1,
        1, -1, -1,
        1,  1, -1,

        //Top
        -1,  1,  1,
        1,  1,  1,
        -1,  1, -1,
        1,  1, -1,

        //Bottom
        -1,  -1,  1,
        1,  -1,  1,
        -1,  -1, -1,
        1,  -1, -1};

    return 0;
}
