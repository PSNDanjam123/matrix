#pragma once
#include "./Core/Matrix.h"

namespace Jim::Matrix {
    template <typename T>
    class Mat4 : public Jim::Matrix::Core::Matrix<Mat4<T>, T> {
        public:
            Mat4() : Jim::Matrix::Core::Matrix<Mat4<T>,T>::Matrix(4,4) {}
            template <typename Num1, typename Num2, typename Num3>
                Mat4& translate(Num1 x, Num2 y, Num3 z) {
                    this->operator()(3,0) = x;
                    this->operator()(3,1) = y;
                    this->operator()(3,2) = z;
                    return *this;
                }
    };
}
