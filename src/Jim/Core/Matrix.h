#pragma once
#include <vector>
#include <functional>
#include <sstream>

namespace Jim::Core {
    template <typename BT>  //Base Type
        class Matrix {
            public:
                Matrix(unsigned rows, unsigned cols) {
                    this->resize(cols, rows);
                }
                Matrix& resize(unsigned cols, unsigned rows) {
                    this->_cols = cols;
                    this->_rows = rows;
                    this->_matrix.resize(this->_rows);
                    unsigned r;
                    for(r = 0; r < this->_rows; r++) {
                        this->_matrix[r].resize(this->_cols);
                    }
                    return *this;
                }
                BT get(unsigned c, unsigned r) {
                    return this->_matrix[r][c];
                }
                Matrix& set(unsigned c, unsigned r, BT val) {
                    this->_matrix[r][c] = val;
                    return *this;
                }
                unsigned cols() {
                    return this->_cols;
                }
                unsigned rows() {
                    return this->_rows;
                }
                Matrix identity() {
                    Matrix<BT> identity(this->_cols, this->_rows);
                    return identity.map([](BT, unsigned& c, unsigned& r) { return (c == r) ? 1 : 0; });
                }
                std::string str() {
                    std::stringstream output;
                    this->forEach([this, &output](BT val, unsigned& c, unsigned&) {
                            output << val << '\t';
                            if(c == this->_cols - 1) {
                            output << '\n';
                            }
                            });
                    return output.str();
                }
                Matrix& forEach(std::function<void (BT val, unsigned& c, unsigned& r)> callback) {
                    unsigned r, c;
                    for(r = 0; r < this->_rows; r++) {
                        for(c = 0; c < this->_cols; c++) {
                            callback(this->_matrix[r][c], c, r);
                        }
                    }
                    return *this;
                }
                Matrix& map(std::function<BT (BT val, unsigned& c, unsigned& r)> callback) {
                    return this->forEach([this, &callback](BT val, unsigned& c, unsigned& r) {
                            this->set(c, r, callback(val, c, r));
                            });
                }
            private:
                unsigned _rows;
                unsigned _cols;
                std::vector<std::vector<BT>> _matrix;
        };
}
