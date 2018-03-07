#pragma once
#include <vector>
#include <functional>

namespace Jim::Matrix::Core {
    template <class C, typename T>
        class Matrix {
            public:
                Matrix(unsigned rows, unsigned cols) : _rows(rows), _cols(cols) {
                    unsigned r, c;
                    for(r = 0; r < this->_rows; r++) {
                        std::vector<T> row;
                        for(c = 0; c < this->_cols; c++) {
                            row.push_back(0);
                        }
                        this->_matrix.push_back(row);
                    }
                }
                virtual T get(unsigned x, unsigned y) {
                    return this->_matrix[y][x];
                }
                virtual C& map(std::function<T (T val, unsigned x, unsigned y)> callback) {
                    this->_map(callback);
                    return this->_chain();
                }
                virtual C& map(std::function<T (T val)> callback) {
                    std::function<T (T val, unsigned x, unsigned y)> callbackFull = [callback](T val, unsigned, unsigned) -> T {
                        return callback(val);
                    };
                    return this->map(callbackFull);
                }
                virtual T& operator() (unsigned x, unsigned y) {
                    return this->_matrix[y][x];
                }
            private:
                std::vector<std::vector<T>> _matrix;
                const unsigned _rows;   //y
                const unsigned _cols;   //x
                C& _chain() {
                    return static_cast<C&>(*this);
                }
                void _map(std::function<T (T val, unsigned x, unsigned y)> callback) {
                    unsigned r, c;
                    for(r = 0; r < this->_rows; r++) {
                        for(c = 0; c < this->_cols; c++) {
                            this->_matrix[r][c] = callback(this->_matrix[r][c], c, r);
                        }
                    }
                }
        };
}
