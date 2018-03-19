#include "./Jim/Component/Core/Object.h"
#include "./Jim/Component/Camera.h"
#include "./Jim/Component/Renderer.h"
#include "./Jim/Core/Math.h"

#include <ncurses.h>
#include <thread>
#include <chrono>
#include <cmath>

using namespace Jim::Core::Math;
using namespace Jim::Component;
using namespace Jim::Component::Core;
using namespace Jim::Core::Types;
using namespace std;

Object cube;
Camera camera;
Renderer renderer;

void handleInput(char ch) {
    unit m = 0.5;   //Move speed
    unit t = 5;     //Turn speed
    matrix o = camera.getOrientation();
    matrix a = {{0},{0},{1},{0}};   //Forward
    matrix b = {{1},{0},{0},{0}};   //Side
    a = o * a;
    b = o * b;
    if(ch == 'w') {
        camera.translate(m * a.get(0,0), 0,-m * a.get(0,2));
    } else if(ch == 's') {
        camera.translate(-m * a.get(0,0),0,m * a.get(0,2));
    } else if(ch == 'a') {
        camera.translate(-m * b.get(0,0),0,m * b.get(0,2));
    } else if(ch == 'd') {
        camera.translate(m * b.get(0,0),0,-m * b.get(0,2));
    } else if(ch == 'l') {
        camera.rotate(0,-t,0);
    } else if(ch == 'j') {
        camera.rotate(0,t,0);
    } else if(ch == 'i') {
        camera.rotate(-t,0,0);
    } else if(ch == 'k') {
        camera.rotate(t,0,0);
    }
}

bool findKey(vector<char> v, char key) {
    return (find(v.begin(), v.end(), key) != v.end());
}

int main(void) {
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

    cube.translate(0,0,-5);

    renderer.addObject(&cube);
    renderer.setCamera(&camera);
    char ch;
    while(true) {
        vector<char> keys = {};
        while((ch = getch()) != ERR) {
            if(!findKey(keys, ch)) {
                keys.push_back(ch);
            }
            handleInput(ch);
        }

        renderer.render();
        this_thread::sleep_for(chrono::microseconds(33333));
    }

    return 0;
}
