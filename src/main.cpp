#include "./Jim/Component/Core/Object.h"
#include "./Jim/Component/Camera.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>

using namespace Jim::Component;
using namespace Jim::Component::Core;
using namespace Jim::Core::Types;
using namespace std;

void render(unit x, unit y) {
    int worldX, worldY;
    unit scalex = 1.5, scaley = 1;
    getmaxyx(stdscr,worldY, worldX);
    unsigned cx = worldX / 2, cy = worldY / 2;
    unsigned ax = cx + x * scalex;
    unsigned ay = cy + y * scaley;
    mvaddch(ay, ax, 'x');
}

int main(void) {
    Object cube;
    Camera camera;

    cube.setVertexBuffer({
            -1,-1,-1,
            -1,-1, 1,
            -1, 1, 1,
            -1, 1,-1,

             1,-1,-1,
             1,-1, 1,
             1, 1, 1,
             1, 1,-1
            });

    cube.setScale(3,3,3);

    initscr();
    curs_set(0);
    noecho();


    while(true) {
        cube.rotate(3,2,1);

        buffer vBuf = cube.getVertexBuffer();
        matrix m = cube.getMatrix() * camera.getProjectionMatrix();

        unsigned i = 0;
        xyz actual = {.x = 0, .y = 0, .z = 0};
        clear();
        for(auto& index : vBuf) {
            i++;
            switch(i) {
                case 1:
                    actual.x = index;
                    break;
                case 2:
                    actual.y = index;
                    break;
                case 3:
                    actual.z = index;
                    matrix vertex(1,4);
                    vertex.set(0,0, actual.x).set(0,1, actual.y).set(0,2, actual.z).set(0,3,1);
                    vertex = m * vertex;
                    vertex.set(0,0, vertex.get(0,0)/vertex.get(0,3)).set(0,1, vertex.get(0,1)/vertex.get(0,3));
                    render(vertex.get(0,0), vertex.get(0,1));
                    actual = {.x = 0, .y = 0, .z = 0};
                    i = 0;
                    break;
            }
        }
        string info = "FOV: " + to_string(camera.getFOV());
        mvprintw(0,0,info.c_str());

        refresh();
        this_thread::sleep_for(chrono::microseconds(33333)); 
    }

    endwin();

    return 0;
}
