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

    initscr();
    curs_set(0);
    noecho();
    timeout(0);
    char ch;

    cube.setScale(3,3,3);

    while(true) {
        cube.rotate(5,4,3);
        ch = getch();
        if(ch != ERR) {
            switch(ch) {
                case 'w':
                    cube.translate(0,0,1);
                    break;
                case 's':
                    cube.translate(0,0,-1);
                    break;
                case 'a':
                    cube.translate(-1,0,0);
                    break;
                case 'd':
                    cube.translate(1,0,0);
                    break;
                case 'j':
                    cube.rotate(0,-1,0);
                    break;
                case 'l':
                    cube.rotate(0,1,0);
                    break;
                case 'i':
                    cube.rotate(-1,0,0);
                    break;
                case 'k':
                    cube.rotate(1,0,0);
                    break;
            }
        }

        buffer vBuf = cube.getVertexBuffer();

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
                    vertex = camera.getProjectionMatrix() * (cube.getMatrix() * vertex);
                    vertex.set(0,0, vertex.get(0,0)/vertex.get(0,3)).set(0,1, vertex.get(0,1)/vertex.get(0,3));
                    render(vertex.get(0,0), vertex.get(0,1));
                    actual = {.x = 0, .y = 0, .z = 0};
                    i = 0;
                    break;
            }
        }
        xyz pos = cube.getPosition();
        xyz rot = cube.getRotation();
        string info = "FOV: " + to_string(camera.getFOV());
        info += "\n\nCUBE POS: x:" + to_string(pos.x) + ", y:" + to_string(pos.y) + ", z:" + to_string(pos.z);
        info += "\nCUBE ROT: x:" + to_string(rot.x) + ", y:" + to_string(rot.y) + ", z:" + to_string(rot.z);
        mvprintw(0,0,info.c_str());

        refresh();
        this_thread::sleep_for(chrono::microseconds(33333)); 
    }

    endwin();

    return 0;
}
