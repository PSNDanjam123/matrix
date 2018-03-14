#include <iostream>
#include <cmath>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;
using namespace std;

#define PI 3.141592

bool running = true;

struct object {
    Matrix<float> x = {{-1},{-1},{0},{1}};
    Matrix<float> y = {{0},{1},{0},{1}};
    Matrix<float> z = {{1},{-1},{0},{1}};
    Matrix<float> pos = {
        {1,0,0,3},
        {0,1,0,3},
        {0,0,1,3},
        {0,0,0,1}
    };
    Matrix<float> rot = {
        {1,0,0,3},
        {0,1,0,3},
        {0,0,1,3},
        {0,0,0,1}
    };
    Matrix<float> mat = {
        {1,0,0,3},
        {0,1,0,3},
        {0,0,1,3},
        {0,0,0,1}
    };
} obj;

void rotate(object& obj, float deg) {
    float rad = deg / 180 * PI;
    Matrix<float> rot = {
        {cos(rad), -sin(rad), 0.0f, 0.0f},
        {sin(rad), cos(rad), 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    obj.rot = rot * obj.rot;
}

void translate(object& obj, float x, float y, float z) {
    Matrix<float> pos = {
        {1.0f, 0.0f, 0.0f, x},
        {0.0f, 1.0f, 0.0f, y},
        {0.0f, 0.0f, 1.0f, z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    obj.pos = pos * obj.pos;
}

void render() {
    while(true) {
        if(running != true) {
            return;
        }
        obj.mat = obj.pos * obj.rot;
        clear();
        Matrix<int> x = obj.mat * obj.x;
        Matrix<int> y = obj.mat * obj.y;
        Matrix<int> z = obj.mat * obj.z;

        mvaddch(x.get(0,0), x.get(0,1), 'x');
        mvaddch(y.get(0,0), y.get(0,1), 'y');
        mvaddch(z.get(0,0), z.get(0,1), 'z');

        refresh();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void input() {
    while(true) {
        if(running != true) {
            return;
        }
        char ch = getch();
        if(ch == 'f') {
            running = false;
            break;
        } else if(ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
            Matrix<float> axis;
            switch(ch) {
                case 'w':
                    axis = {{0},{1},{0},{0}};
                    break;
                case 's':
                    axis = {{0}, {-1},{0},{0}};
                    break;
                case 'a':
                    axis = {{-1},{0},{0},{0}};
                    break;
                case 'd':
                    axis = {{1},{0},{0},{0}};
                    break;
            };
            axis = obj.mat * axis;
            translate(obj, axis.get(0,0), axis.get(0,1), axis.get(0,2));
        } else if(ch == 'q' || ch == 'e') {
            switch(ch) {
                case 'q':
                    rotate(obj, -1);
                    break;
                case 'e':
                    rotate(obj, 1);
            }
        }
    }
}

int main(void) {
    initscr();
    curs_set(0);
    noecho();
    
    std::thread in(input);
    std::thread re(render);

    in.join();
    re.join();

    endwin();

    return 0;
}
