#include "./ship.h"

#include <cmath>
#include <thread>
#include <chrono>
#include <ncurses.h>

using namespace std;

bool Ship::running = true;

Ship::ship Ship::USS_Ent;

void Ship::init() {
    initscr();
    curs_set(0);
    noecho();

    thread re(Ship::threadRender);
    thread si(Ship::threadSimulate);
    thread in(Ship::threadInput);

    re.join();
    si.join();
    in.join();

    endwin();
}

void Ship::rotate(Ship::object& obj, float deg) {
    float r = degToRad(deg);
    Matrix<float> m = {
        { cos(r),-sin(r),   0.0f,   0.0f},
        { sin(r), cos(r),   0.0f,   0.0f},
        {   0.0f,   0.0f,   1.0f,   0.0f},
        {   0.0f,   0.0f,   0.0f,   1.0f}
    };
    obj.rotation = m * obj.rotation;
}

void Ship::translate(Ship::object& obj, float x, float y, float z) {
    Matrix<float> m = {
        { 1.0f, 0.0f, 0.0f,    x},
        { 0.0f, 1.0f, 0.0f,    y},
        { 0.0f, 0.0f, 1.0f,    z},
        { 0.0f, 0.0f, 0.0f, 1.0f}
    };
    obj.translation = m * obj.translation;
}

void Ship::scale(Ship::object& obj, float x, float y, float z) {
    Matrix<float> m = {
        {    x, 0.0f, 0.0f, 0.0f},
        { 0.0f,    y, 0.0f, 0.0f},
        { 0.0f, 0.0f,    z, 0.0f},
        { 0.0f, 0.0f, 0.0f, 1.0f}
    };
    obj.scale = m * obj.scale;
}

float Ship::degToRad(float deg) {
    return deg / 180 * PI;
}

float Ship::radToDeg(float rad) {
    return rad * 180 / PI;
}

void Ship::threadRender() {
    while(true) {
        Matrix<int> x = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.x;
        Matrix<int> y = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.y;
        Matrix<int> z = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.z;

        clear();
        mvaddch(x.get(0,0), x.get(0,1), 'o');
        mvaddch(y.get(0,0), y.get(0,1), 'O');
        mvaddch(z.get(0,0), z.get(0,1), 'o');
        refresh();

        this_thread::sleep_for(chrono::milliseconds(33));
    }
}

void Ship::threadSimulate() {
    while(true) {
        if(Ship::running == false) {
            return;
        }

        if(Ship::USS_Ent.dampener == true) {
            float dampen = Ship::USS_Ent.thrust / 2;
            float& spin = Ship::USS_Ent.spin;
            Matrix<float>& force = Ship::USS_Ent.force;
            float x = force.get(0,0);
            float y = force.get(0,1);
            float z = force.get(0,2);
            if(spin != 0) {
                spin += dampen * ((spin > 0) ? -1 : 1);
            }
            if(x != 0) {
                force.set(0,0,dampen * ((x > 0) ? -1 : 1) + x);
            }
            if(y != 0) {
                force.set(0,1,dampen * ((x > 0) ? -1 : 1) + y);
            }
            if(z != 0) {
                force.set(0,2,dampen * ((x > 0) ? -1 : 1) + z);
            }
        }

        Ship::translate(Ship::USS_Ent.object, Ship::USS_Ent.force.get(0,0), Ship::USS_Ent.force.get(0,1), Ship::USS_Ent.force.get(0,2));
        Ship::rotate(Ship::USS_Ent.object, Ship::USS_Ent.spin);
        Ship::USS_Ent.object.matrix = Ship::USS_Ent.object.translation * Ship::USS_Ent.object.rotation;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

void Ship::threadInput() {
    char ch;
    char prevCh;
    Matrix<float> axis;

    while(true) {
        if(Ship::running == false) {
            return;
        }
        ch = getch();
        if(ch == 'f') { //Quit
            Ship::running = false;
            return;
        } else if(ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {   //Move
            switch(ch) {
                case 'w':
                    axis = {{ 0},{-1},{ 0},{ 0}};
                    break;
                case 's':
                    axis = {{ 0},{ 1},{ 0},{ 0}};
                    break;
                case 'a':
                    axis = {{-1},{ 0},{ 0},{ 0}};
                    break;
                case 'd':
                    axis = {{ 1},{ 0},{ 0},{ 0}};
                    break;
            }
            Ship::USS_Ent.force += Ship::USS_Ent.object.matrix * axis * Ship::USS_Ent.thrust;
        } else if(ch == 'q' || ch == 'e') { //Rotate
            switch(ch) {
                case 'q':
                    Ship::USS_Ent.spin -= Ship::USS_Ent.thrust;
                    break;
                case 'e':
                    Ship::USS_Ent.spin += Ship::USS_Ent.thrust;
                    break;
            }
        } else if(ch == 'i' && prevCh != ch) {  //Toggle Dampener
            Ship::USS_Ent.dampener = !Ship::USS_Ent.dampener;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
        prevCh = ch;
    }
}