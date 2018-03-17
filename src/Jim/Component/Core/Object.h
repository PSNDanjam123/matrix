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
            virtual rBuffer getVertexBuffer();
            virtual void setVertexBuffer(list1d);
            virtual void setVertexBuffer(buffer);
            virtual xyz getPosition();
            virtual xyz getRotation();
            virtual xyz getScale();
            virtual void translate(unit x, unit y, unit z);
            virtual void transform(unit x, unit y, unit z);
            virtual void rotate(unit x, unit y, unit z);
            virtual void scale(unit x);
            virtual void setPosition(unit x, unit y, unit z);
            virtual void setRotation(unit x, unit y, unit z);
            virtual void setScale(unit x, unit y, unit z);
            virtual matrix getMatrix();
            virtual matrix getTranslationMatrix();
            virtual matrix getRotationMatrix();
            virtual matrix getRotationXMatrix();
            virtual matrix getRotationYMatrix();
            virtual matrix getRotationZMatrix();
            virtual matrix getTransformationMatrix();
        private:
            buffer _vertexBuffer;
            xyz _position;
            xyz _rotation;
            xyz _scale;
    };
}
