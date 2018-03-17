#pragma once
#include "./Core/Object.h"
#include "./Camera.h"
#include <vector>

using namespace Jim::Component;
using namespace Jim::Component::Core;
using namespace std;

namespace Jim::Component {
    class Renderer {
        public:
            typedef struct pixel {
                Object* object = 0;
                xyz position;
            } pixel;
            Renderer();
            ~Renderer();
            void clear();
            void setCamera(Camera* camera);
            void addObject(Object* object);
            xyz getScreenSize();
            void render();
            void renderObjects();
        private:
            vector<pixel> _pixels;
            Camera* _camera;
            vector<Object*> _objects;
            vector<Object> _renderedObjects;
    };
}
