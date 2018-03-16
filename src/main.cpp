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

    cube1.translate(0.0f, 0.0f, -1.0f);
    cube2.translate(-3.0f, 0.0f, -1.0f);
    cube3.translate(3.0f, 0.0f, -2.0f);
    cube3.transform(1.0, 2.0, 1.0);

    world.objects.push_back(&cube1);
    world.objects.push_back(&cube2);
    world.objects.push_back(&cube3);

    initscr();
    curs_set(0);
    noecho();

    char ch = 'a';

    while(ch != 'q') {
        ch = getch();
        if(ch == 'a') {
            world.camera.translate(-1.0f, 0.0f, 0.0f);
        } else if(ch == 'd') {
            world.camera.translate(1.0f, 0.0f, 0.0f);
        } else if(ch == 'w') {
            world.camera.translate(0.0f, 0.0f, -1.0f);
        } else if(ch == 's') {
            world.camera.translate(0.0f, 0.0f, 1.0f);
        } else if(ch == 'r') {
            world.camera.translate(0.0f, 1.0f, 0.0f);
        } else if(ch == 'f') {
            world.camera.translate(0.0f,-1.0f, 0.0f);
        } else if(ch == 'i') {
            cube1.rotateX(1.0f);
        } else if(ch == 'k') {
            cube1.rotateX(-1.0f);
        } else if(ch == 'j') {
            cube1.rotateY(-1.0f);
        } else if(ch == 'l') {
            cube1.rotateY(1.0f);
        } else if(ch == 'u') {
            world.camera.setFOV(world.camera.getFOV() - 0.01);
        } else if(ch == 'y') {
            world.camera.setFOV(world.camera.getFOV() + 0.01);
        }

        clear();
        world.tick();
        std::string controls = "CAMERA: cam-wasdrf;cube-ijkl;quit-q;fov-yu;";
        std::string stats = "STATS: fov-" + std::to_string(world.camera.getFOV() * 100) + ";";

        mvprintw(0,0, controls.c_str());
        mvprintw(1,0, stats.c_str());
        refresh();
    }

    endwin();

    return 0;
}
