#pragma once
#include "../../Core/Types.h"
#include <vector>
#include <mutex>

using namespace Jim::Core::Types;
using namespace std;

namespace Jim::Component::Core {
    class Object {
        public:
            Object();
            rBuffer getVertexBuffer();
            void setVertexBuffer(list1d);
            void setVertexBuffer(buffer);
            xyz getPosition();
            xyz getRotation();
            xyz getScale();
            void translate(unit x, unit y, unit z);
            void transform(unit x, unit y, unit z);
            void rotate(unit x, unit y, unit z);
            void scale(unit x);
            void setPosition(unit x, unit y, unit z);
            void setRotation(unit x, unit y, unit z);
            void setScale(unit x, unit y, unit z);
            matrix getMatrix();
            matrix getTranslationMatrix();
            matrix getRotationMatrix();
            matrix getRotationXMatrix();
            matrix getRotationYMatrix();
            matrix getRotationZMatrix();
            matrix getTransformationMatrix();
        private:
            buffer _vertexBuffer;
            xyz _position;
            xyz _rotation;
            xyz _scale;
            mutex _mutex;
    };
}
