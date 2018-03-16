#pragma once
#include "./Core/Object.h"

using namespace Jim::Component::Core;

namespace Jim::Component {
    class Camera : Object {
        public:
            Camera();
            void setFOV(unit fov);
            unit getFOV(); 
            matrix getProjectionMatrix();
        private:
            Object _viewer;
    };
}
