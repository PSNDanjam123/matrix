#pragma once
#include <vector>

namespace Jim::Core {
    template <typename T>
        class Matrix {
            public:
                Matrix(unsigned cols, unsigned rows) {
                    this->resize(cols, rows);
                }
                Matrix resize(unsigned& cols, unsigned& rows) { 
                    this->_cols = cols;
                    this->_rows = rows;
                    this->_matrix.resize(this->_rows);
                    unsigned r;
                    for(r = 0; r < this->_rows; r++) {
                        this->_matrix[r].resize(this->_cols);
                    }
                }
            private:
                std::vector<std::vector<T>> _matrix;
                unsigned _cols;
                unsigned _rows;
        };
}
