#include "./Jim/Core/World.h"
using namespace Jim::Core;

int main(void) {
    std::initializer_list<double> cube = {
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

    Object cube1 = cube;
    Object cube2 = cube;
    Object cube3 = cube;

    World world(500,500,500);

    world.objects.push_back(&cube1);
    world.objects.push_back(&cube2);
    world.objects.push_back(&cube3);

    cube2.translate(5.0f,5.0f,5.0f);
    cube2.transform(5.0,5.0,5.0);

    cube3.translate(6.0f, 1.0f, 10.0f);
    cube3.transform(7.0,7.0,7.0);

    world.tick();

    return 0;
}
