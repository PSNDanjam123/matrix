#pragma once
#include <iostream>
#include "./Core/Matrix.h"

namespace Jim::Matrix {
    template <typename T>
    class Mat3 : public Jim::Matrix::Core::Matrix<Mat3<T>, T> {
        public:
            Mat3() : Jim::Matrix::Core::Matrix<Mat3<T>,T>::Matrix(3,3) {}
    };
}
