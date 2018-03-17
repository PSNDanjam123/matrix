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
        if(ch == 'w') {
            cube.rotate(3,0,0);
        }
        renderer.render();
        this_thread::sleep_for(chrono::microseconds(33333));
    }

    return 0;
}
