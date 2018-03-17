#include "./Jim/Component/Core/Object.h"
#include "./Jim/Component/Camera.h"
#include "./Jim/Component/Renderer.h"

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

    renderer.addObject(&cube);
    renderer.setCamera(&camera);
    renderer.renderObjects(); 

    return 0;
}
