#include <ncurses.h>
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

    cube1.translate(0.0f,0.0f, -1.0f);
    cube1.transform(2.0,2.0,2.0);

    world.objects.push_back(&cube1);

    initscr();
    curs_set(0);
    noecho();

    char ch = 'a';

    while(ch != 'q') {
        cube1.rotateY(5.0f);
        ch = getch();
        if(ch == 'a') {
            world.camera.translate(-1.0f, 0.0f, 0.0f);
        } else if(ch == 'd') {
            world.camera.translate(1.0f, 0.0f, 0.0f);
        } else if(ch == 'w') {
            world.camera.translate(0.0f, 0.0f, 1.0f);
        } else if(ch == 's') {
            world.camera.translate(0.0f, 0.0f, -1.0f);
        }
        clear();
        world.tick();
        refresh();
    }

    endwin();

    return 0;
}
