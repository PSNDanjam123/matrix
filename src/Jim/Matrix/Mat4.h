#pragma once
#include <iostream>
#include "./Core/Matrix.h"

namespace Jim::Matrix {
    template <typename T>
    class Mat4 : public Jim::Matrix::Core::Matrix<Mat4<T>, T> {
        public:
            Mat4() : Jim::Matrix::Core::Matrix<Mat4<T>,T>::Matrix(4,4) {}
    };
}
