#pragma once
#include "./Matrix.h"

namespace Jim::Core {
    class Object {
        typedef Matrix<float> matrix;
        typedef std::vector<matrix> matrices;
        public:
            Object();
            void translate(float x, float y, float z);
            void scale(float amount);
            void scale(float x, float y, float z);
        private:
            matrix* _matrix;
            matrix _localMatrix;
            matrix _worldMatrix;
    };
}
