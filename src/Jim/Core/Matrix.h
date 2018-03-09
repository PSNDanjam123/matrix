#pragma once
#include <vector>
#include <functional>
#include <sstream>
#include <string>


namespace Jim::Core {
    template <typename T>
        class Matrix {
            public:
                Matrix(unsigned cols, unsigned rows) {
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
                std::string str() {
                    std::stringstream output;
                    this->_forEach([this, &output](T val, unsigned& c, unsigned&) {
                            output << val << '\t';
                            if(c == this->_cols - 1) {
                                output << '\n';
                            }
                            });
                    return output.str();
                }
                Matrix& forEach(std::function<void (T val, unsigned& c, unsigned& r)> callback) {
                    return this->_forEach(callback);
                }
                Matrix& map(std::function<T (T val, unsigned& c, unsigned& r)> callback) {
                    return this->_map(callback);
                }
                Matrix& set(unsigned c, unsigned r, T val) {
                    this->_matrix[r][c] = val;
                    return *this;
                }
                T get(unsigned c, unsigned r) {
                    return this->_matrix[r][c];
                }
                unsigned cols() {
                    return this->_cols;
                }
                unsigned rows() {
                    return this->_rows;
                }
                Matrix identity() {
                    Matrix<T> identity(this->_cols, this->_rows);
                    return identity.map([](T, unsigned& c, unsigned& r) {return (c == r) ? 1 : 0;});
                }
                template <class M>
                    friend typename std::enable_if<std::is_class<M>::value, Matrix>::type operator*(Matrix& lmat, M& rmat) {
                        Matrix<T> res(lmat.cols(), rmat.rows());
                        unsigned i;
                        return res.map([&i, &lmat, &rmat](T val, unsigned& c, unsigned& r) {
                                for(i = 0; i < rmat.cols(); i++) {
                                    val += rmat.get(i, r) * lmat.get(c, i);
                                }
                                return val;
                                });
                    }
            private:
                std::vector<std::vector<T>> _matrix;
                unsigned _cols;
                unsigned _rows;
                Matrix& _forEach(std::function<void (T val, unsigned& c, unsigned& r)> callback) {
                    unsigned r, c;
                    for(r = 0; r < this->_rows; r++) {
                        for(c = 0; c < this->_cols; c++) {
                            callback(this->_matrix[r][c], c, r);
                        }
                    }
                    return *this;
                }
                Matrix& _map(std::function<T (T val, unsigned& c, unsigned& r)> callback) {
                    return this->_forEach([this, &callback](T val, unsigned& c, unsigned& r) {
                            this->set(c,r, callback(val, c, r));
                            });
                }
        };
}
