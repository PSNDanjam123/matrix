#include "./Jim/Component/Core/Object.h"
#include "./Jim/Component/Camera.h"
#include "./Jim/Component/Renderer.h"

#include <ncurses.h>
#include <thread>
#include <chrono>

using namespace Jim::Component;
using namespace Jim::Component::Core;
using namespace Jim::Core::Types;
using namespace std;

int main(void) {
    Object cube;
    Camera camera;
    Renderer renderer;

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
        ch = getch();

        matrix camRot = camera.getRotationMatrix();
        matrix camCur(1,4); //The local xyz after all the rotations
        unit speed = 0.1;
        unit rotSpeed = 1;

        if(ch == 'w') {
            camCur = {{0.0},{0.0},{-speed},{0.0}};
            camCur = camRot * camCur;
            camera.translate(camCur.get(0,0), camCur.get(0,1), camCur.get(0,2));
        } else if(ch == 's') {
            camCur = {{0.0},{0.0},{speed},{0.0}};
            camCur = camRot * camCur;
            camera.translate(camCur.get(0,0), camCur.get(0,1), camCur.get(0,2));
        } else if(ch == 'a') {
            camCur = {{-speed},{0.0},{0.0},{0.0}};
            camCur = camRot * camCur;
            camera.translate(camCur.get(0,0), camCur.get(0,1), camCur.get(0,2));
        } else if(ch == 'd') {
            camCur = {{speed},{0.0},{0.0},{0.0}};
            camCur = camRot * camCur;
            camera.translate(camCur.get(0,0), camCur.get(0,1), camCur.get(0,2));
        } else if(ch == 'j') {
            camera.rotate(0,rotSpeed,0);
        } else if(ch == 'l') {
            camera.rotate(0,-rotSpeed,0);
        }
        renderer.render();
        this_thread::sleep_for(chrono::microseconds(33333));
    }

    return 0;
}
