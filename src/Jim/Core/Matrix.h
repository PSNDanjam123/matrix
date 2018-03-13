#pragma once
#include <vector>
#include <functional>
#include <sstream>

namespace Jim::Core {
    template <typename BT>  //Base Type
        class Matrix {
            public:
                Matrix() {
                    this->resize(0,0);
                }
                Matrix(unsigned cols, unsigned rows) {
                    this->resize(cols, rows);
                }
                template <typename T>
                    Matrix(std::initializer_list<T> list) {
                        this->operator=(list);
                    }
                template <typename T>
                    Matrix(std::initializer_list<std::initializer_list<T>> list) {
                        this->operator=(list);
                    }
                template <typename T>
                    Matrix(Matrix<T> mat) {
                        this->operator=(mat);
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
                    if(c >= this->cols() || r >= this->rows()) {
                        throw std::runtime_error("Cannot get because col/row is out of range");
                    }
                    return this->_matrix[r][c];
                }
                Matrix& set(unsigned c, unsigned r, BT val) {
                    if(c >= this->cols() || r >= this->rows()) {
                        throw std::runtime_error("Cannot set because col/row is out of range");;
                    }
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
                template <typename T>
                    static Matrix convertList(std::initializer_list<T> list) {
                        Matrix<BT> mat(list.size(), 1);
                        return mat.map([list](BT, unsigned& c, unsigned&) {
                                return list.begin()[c];
                                });
                    }
                template <typename T>
                    static Matrix convertList(std::initializer_list<std::initializer_list<T>> list) {
                        unsigned cols = list.begin()[0].size();
                        for(auto& item : list) {
                            if(cols != item.size()) {
                                throw std::runtime_error("Matrix rows do not have the same number of columns");
                            }
                        }
                        Matrix<BT> mat(cols, list.size());
                        mat.map([&list] (BT, unsigned& c, unsigned& r) {
                                return list.begin()[r].begin()[c];
                                });
                        return mat;
                    }
                template <typename T>
                    Matrix& operator*=(std::initializer_list<T> list) {
                        return operator*=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator*=(std::initializer_list<std::initializer_list<T>> list) {
                        return operator*=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator*=(Matrix<T> rmat) {
                        if(this->cols() != rmat.rows()) {
                            throw std::runtime_error("Matrices cannot be multiplied because of row/col mismatch");
                        }
                        Matrix<BT> res(rmat.cols(), this->rows());
                        unsigned i;
                        res.map([&i, this, &rmat](BT val, unsigned& c, unsigned& r) {
                                for(i = 0; i < this->cols(); i++) {
                                val += this->get(i,r) * rmat.get(c,i);
                                }
                                return val;
                                });
                        *this = res;
                        return *this;
                    }
                template <typename T>
                    friend Matrix operator*(Matrix lmat, Matrix<T> rmat) {
                        return lmat *= rmat;
                    }
                template <typename N>
                    typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix&> operator*=(N num) {
                        this->map([this, &num](BT val, unsigned&, unsigned&) {return val *= num;});
                        return *this;
                    }
                template <typename N>
                    friend typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix> operator*(Matrix lmat, N num) {
                        return lmat *= num;
                    }
                template <typename N>
                    friend typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix> operator*(N num, Matrix rmat) {
                        return rmat *= num;
                    }
                template <typename T>
                    Matrix& operator+=(std::initializer_list<T> list) {
                        return this->operator+=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator+=(std::initializer_list<std::initializer_list<T>> list) {
                        return this->operator+=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator+=(Matrix<T> rmat) {
                        if(this->rows() != rmat.rows() || this->cols() != rmat.cols()) {
                            throw std::runtime_error("Matrices cannot be added because they have different dimensions");
                        }
                        this->map([&rmat](BT val, unsigned& c, unsigned& r) {
                                return val + rmat.get(c,r);
                                });
                        return *this;
                    }
                template <typename T>
                    friend Matrix operator+(Matrix lmat, Matrix<T> rmat) {
                        return lmat += rmat;
                    }
                template <typename N>
                    typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix&> operator+=(N num) {
                        this->map([&num](BT val, unsigned&, unsigned&) {
                                return val + num;
                                });
                        return *this;
                    }
                template <typename N>
                    friend typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix> operator+(Matrix lmat, N num) {
                        return lmat += num;
                    }
                template <typename N>
                    friend typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix> operator+(N num, Matrix rmat) {
                        return rmat += num;
                    }
                template <typename T>
                    Matrix& operator-=(std::initializer_list<T> list) {
                        return this->operator-=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator-=(std::initializer_list<std::initializer_list<T>> list) {
                        return this->operator-=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator-=(Matrix<T> rmat) {
                        if(this->rows() != rmat.rows() || this->cols() != rmat.cols()) {
                            throw std::runtime_error("Matrices cannot be subtracted because they have different dimensions");
                        }
                        this->map([&rmat](BT val, unsigned& c, unsigned& r) {
                                return val - rmat.get(c,r);
                                });
                        return *this;
                    }
                template <typename T>
                    friend Matrix operator-(Matrix lmat, Matrix<T> rmat) {
                        return lmat -= rmat;
                    }
                template <typename N>
                    typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix&> operator-=(N num) {
                        this->map([&num](BT val, unsigned&, unsigned&) {
                                return val - num;
                                });
                        return *this;
                    }
                template <typename N>
                    friend typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix> operator-(Matrix lmat, N num) {
                        return lmat -= num;
                    }
                template <typename N>
                    friend typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix> operator-(N num, Matrix rmat) {
                        return rmat -= num;
                    }
                template <typename T>
                    Matrix& operator=(std::initializer_list<T> list) {
                        return this->operator=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator=(std::initializer_list<std::initializer_list<T>> list) {
                        return this->operator=(this->convertList(list));
                    }
                template <typename T>
                    Matrix& operator=(Matrix<T> rmat) {
                        this->resize(rmat.cols(), rmat.rows());
                        this->map([&rmat](BT, unsigned& c, unsigned& r) {
                                return rmat.get(c,r);
                                });
                        return *this;
                    }
                template <typename N>
                    typename std::enable_if_t<std::is_arithmetic_v<N>, Matrix&> operator=(N num) {
                        this->map([&num](BT, unsigned&, unsigned&) {
                                return num;
                                });
                        return *this;
                    }
            private:
                unsigned _rows;
                unsigned _cols;
                std::vector<std::vector<BT>> _matrix;
        };
}
