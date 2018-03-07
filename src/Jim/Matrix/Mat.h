#pragma once
#include "./Core/Matrix.h"

namespace Jim::Matrix {
    template <typename T>
        class Mat : public Jim::Matrix::Core::Matrix<Mat<T>, T> {
            public:
                Mat(unsigned rows, unsigned cols) : Jim::Matrix::Core::Matrix<Mat<T>,T>::Matrix(rows, cols) {

                }
        };
}
