#pragma once
#include <vector>
#include "./Object.h"

namespace Jim::Core {
    class Camera {
        public:
            Camera();
            void setFOV(float fov);
            float getFOV();
            float FOVToZ(float fov);
            float ZToFOV(float z);
            std::vector<std::vector<Object::matrix>> render(std::vector<std::vector<Object::matrix>>&);
        private:
            float _fov;
    };
}
