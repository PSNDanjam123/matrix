#include "./ship.h"

#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>
#include <ncurses.h>

using namespace std;

mutex Ship::ncurseMutex;
mutex Ship::modify;

bool Ship::running = true;

Ship::ship Ship::USS_Ent;

void Ship::init() {
    {
        std::lock_guard<mutex> lock(Ship::ncurseMutex);
        initscr();
        curs_set(0);
        noecho();
        timeout(0);
    }

    thread re(Ship::threadRender);
    thread si(Ship::threadSimulate);
    thread in(Ship::threadInput);
    thread in2(Ship::threadInput);

    re.join();
    si.join();
    in.join();
    in2.join();

    running = false;
    std::lock_guard<mutex> locak(Ship::ncurseMutex);
    endwin();
}

void Ship::setPos(Ship::object& obj, float x, float y, float z) {
    Ship::translate(obj, -obj.translation.get(3,0) + x, -obj.translation.get(3,1) + y, -obj.translation.get(3,2) + z);
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
    float consoleHeight = 1;
    float consoleWidth = 2;

    int world_x, world_y;
    {
        lock_guard<mutex> lock(ncurseMutex);
        getmaxyx(stdscr, world_y, world_x);
    }

    Ship::setPos(Ship::USS_Ent.object, world_x / consoleWidth / 2, world_y / consoleHeight / 2, 0);

    while(true) {
        string info = "";
        Matrix<float> c, x, y ,z;
        {
            lock_guard<mutex> lock(modify);
            if(Ship::USS_Ent.dampener == true) {
                info += "DAM: #, ";
            } else {
                info += "DAM:  , ";
            }

            c = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.c;
            x = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.x;
            y = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.y;
            z = Ship::USS_Ent.object.matrix * Ship::USS_Ent.object.z;

            if(c.get(0,0) * consoleWidth > world_x) {
                Ship::setPos(Ship::USS_Ent.object, 0, c.get(0,1), c.get(0,2));
            } else if(c.get(0,0) < 0) {
                Ship::setPos(Ship::USS_Ent.object, world_x / consoleWidth, c.get(0,1), c.get(0,2));
            }

            if(c.get(0,1) * consoleHeight > world_y) {
                Ship::setPos(Ship::USS_Ent.object, c.get(0,0), 0, c.get(0,2));
            } else if(c.get(0,1) < 0) {
                Ship::setPos(Ship::USS_Ent.object, c.get(0,0), world_y / consoleHeight, c.get(0,2));
            }

        }
        {
            lock_guard<mutex> lock(ncurseMutex);
            clear();
            mvaddch(consoleHeight * c.get(0,1), consoleWidth * c.get(0,0), 'x');
            mvaddch(consoleHeight * x.get(0,1), consoleWidth * x.get(0,0), 'O');
            mvaddch(consoleHeight * y.get(0,1), consoleWidth * y.get(0,0), '@');
            mvaddch(consoleHeight * z.get(0,1), consoleWidth * z.get(0,0), 'O');
            mvprintw(0,0, info.c_str());
            refresh();
        }

        this_thread::sleep_for(chrono::milliseconds(33));
    }
}

void Ship::threadSimulate() {

    while(true) {
        {
            lock_guard<mutex> lock(modify);
            if(Ship::running == false) {
                return;
            }

            if(Ship::USS_Ent.dampener == true) {
                float dampen = Ship::USS_Ent.thrust / 10;
                float& spin = Ship::USS_Ent.spin;
                Matrix<float>& force = Ship::USS_Ent.force;
                float x = force.get(0,0);
                float y = force.get(0,1);
                if(spin != 0) {
                    spin += dampen * ((spin > 0) ? -1 : 1) * 2;
                }
                if(x != 0) {
                    force.set(0,0,dampen * ((x > 0) ? -1 : 1) + x);
                }
                if(y != 0) {
                    force.set(0,1,dampen * ((y > 0) ? -1 : 1) + y);
                }
            }

            Ship::translate(Ship::USS_Ent.object, Ship::USS_Ent.force.get(0,0), Ship::USS_Ent.force.get(0,1), Ship::USS_Ent.force.get(0,2));
            Ship::rotate(Ship::USS_Ent.object, Ship::USS_Ent.spin);
            Ship::USS_Ent.object.matrix = Ship::USS_Ent.object.scale * Ship::USS_Ent.object.translation * Ship::USS_Ent.object.rotation;
        }
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

void Ship::threadInput() {
    char ch;
    char prevCh;
    Matrix<float> axis;

    while(true) {
        {
            lock_guard<mutex> lock(modify);
            if(Ship::running == false) {
                return;
            }
            {
                lock_guard<mutex> lock(ncurseMutex);
                ch = getch();
            }
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
                        Ship::USS_Ent.spin -= Ship::USS_Ent.thrust * 3;
                        break;
                    case 'e':
                        Ship::USS_Ent.spin += Ship::USS_Ent.thrust * 3;
                        break;
                }
            } else if(ch == 'i' && prevCh != ch) {  //Toggle Dampener
                Ship::USS_Ent.dampener = !Ship::USS_Ent.dampener;
            }
            prevCh = 0;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
