#include "./Jim/Core/Matrix.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <ncurses.h>
using namespace Jim::Core;

#define PI 3.141592653

struct triangle {
    Matrix<float> p1 = Matrix<float>(1,4);
    Matrix<float> p2 = Matrix<float>(1,4);
    Matrix<float> p3 = Matrix<float>(1,4);
};

float degToRad(float deg) {
    return deg*PI/180;
}

float radToDeg(float rad) {
    return rad/PI*180;
}

void rotateZ(triangle& t, float deg) {
    Matrix<float> rot(4,4);
    float rad = degToRad(deg);
    rot = rot.identity();
    rot.set(0,0, std::cos(rad))
        .set(1,0, -std::sin(rad))
        .set(0,1, std::sin(rad))
        .set(1,1, std::cos(rad));
    t.p1 = rot * t.p1;
    t.p2 = rot * t.p2;
    t.p3 = rot * t.p3;
}

void translate(triangle& t, float x, float y, float z) {
    Matrix<float> tra(4,4);
    tra = tra.identity();
    tra.set(3,0, x)
        .set(3,1, y)
        .set(3,2, z);
    t.p1 = tra * t.p1;
    t.p2 = tra * t.p2;
    t.p3 = tra * t.p3;
}

void scale(triangle& t, float a) {
    Matrix<float> sca(4,4);
    sca = sca.identity();
    sca.set(0,0,a).set(1,1,a).set(2,2,a).set(3,3,a);
    t.p1 = sca * t.p1;
    t.p2 = sca * t.p2;
    t.p3 = sca * t.p3;
}

void printVertex(Matrix<float>& m, char output) {
    mvaddch(std::round(m.get(0,1)), std::round(m.get(0,0)), output);
}

int main(void) {
    initscr();

    float rot = 0;

    while(true) {
        clear();

        triangle t;

        t.p1.set(0,0, -1).set(0,1, -1).set(0,3,1);
        t.p2.set(0,0,  0).set(0,1,  1).set(0,3,1);
        t.p3.set(0,0,  1).set(0,1, -1).set(0,3,1);

        scale(t, 5);
        rotateZ(t, rot += 0.1);
        translate(t, 10, 2, 0);

        printVertex(t.p1, 'x');
        printVertex(t.p2, 'y');
        printVertex(t.p3, 'z');

        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    endwin();


    return 0;
}
