#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <functional>

namespace Jim::Matrix::Core {
    template <class C, typename T>
        class Matrix {
            public:
                Matrix(unsigned cols, unsigned rows) : _rows(rows), _cols(cols) {
                    unsigned r, c;
                    for(r = 0; r < this->_rows; r++) {
                        std::vector<T> row;
                        for(c = 0; c < this->_cols; c++)
                            row.push_back(0);
                        this->_matrix.push_back(row);
                    }
                }
                virtual T get(unsigned& x, unsigned& y) {
                    return this->_matrix[y][x];
                }
                virtual C& forEach(std::function<void (T val, unsigned& x, unsigned& y)> callback) {
                    return this->_forEach(callback);
                }
                virtual C& map(std::function<T (T val, unsigned& x, unsigned& y)> callback) {
                    return this->_map(callback);
                }
                virtual C& map(std::function<T (T val)> callback) {
                    return this->map([callback](T val, unsigned&, unsigned&) {return callback(val);});
                }
                virtual C clone() {
                    return this->_chain();
                }
                virtual C identity() {
                    return this->clone().map([](T, unsigned& x, unsigned& y) {return (x == y) ? 1 : 0;});
                }
                virtual std::string str() {
                    std::stringstream output;
                    this->_forEach([this, &output](T val, unsigned& x, unsigned&) {
                            output << val << '\t';
                            if(x == this->_cols - 1)
                            output << '\n';});
                    return output.str();
                }
                virtual T& operator() (unsigned x, unsigned y) {
                    return this->_matrix[y][x];
                }
                template <class Mat>
                    typename std::enable_if<std::is_class<Mat>::value, bool>::type operator==(Mat& mat) {
                        bool result = true;
                        mat.forEach([this, &result](T val, unsigned& x, unsigned& y) {
                                if(this->_matrix[y][x] != val)
                                result = false;});
                        return result;
                    }
                template <class Mat>
                    typename std::enable_if<std::is_class<Mat>::value, bool>::type operator!=(Mat& mat) {
                        return !this->operator==(mat);
                    }
                template <class Mat>
                    typename std::enable_if<std::is_class<Mat>::value, C&>::type operator+= (Mat mat) {
                        if(this->_cols != mat.cols() || this->_rows != mat.rows())
                            exit(EXIT_FAILURE);
                        return this->map([&mat](float val, unsigned& x, unsigned& y) {return val + mat(x,y);});
                    }
                template <typename Num>
                    typename std::enable_if<std::is_convertible<Num, T>::value, C&>::type operator+= (Num val2) {
                        return this->map([&val2](float val) {return val + val2;});
                    }
                template <class Mat>
                    typename std::enable_if<std::is_class<Mat>::value, C&>::type operator-= (Mat mat) {
                        if(this->_cols != mat.cols() || this->_rows != mat.rows())
                            exit(EXIT_FAILURE);
                        return this->map([&mat](float val, unsigned& x, unsigned& y) {return val - mat(x,y);});
                    }
                template <typename Num>
                    typename std::enable_if<std::is_convertible<Num, T>::value, C&>::type operator-= (Num val2) {
                        return this->map([&val2](float val) {return val - val2;});
                    }
                template<class Mat>
                    friend typename std::enable_if<std::is_class<Mat>::value, C>::type operator+(C lmat, Mat rmat) {
                        return lmat.map([&rmat](T val, unsigned& x, unsigned& y) {return val + rmat.get(x, y);});
                    }
                template<typename Num>
                    friend typename std::enable_if<std::is_convertible<Num, T>::value, C>::type operator+(C lmat, Num val2) {
                        return lmat.map([&val2](T val1) {return val1 + val2;});
                    }
                template<typename Num>
                    friend typename std::enable_if<std::is_convertible<Num, T>::value, C>::type operator+(Num val2, C rmat) {
                        return rmat.map([&val2](T val1) {return val1 + val2;});
                    }
                template<class Mat>
                    friend typename std::enable_if<std::is_class<Mat>::value, C>::type operator-(C lmat, Mat rmat) {
                        return lmat.map([&rmat](T val, unsigned& x, unsigned& y) {return val - rmat.get(x, y);});
                    }
                template<typename Num>
                    friend typename std::enable_if<std::is_convertible<Num, T>::value, C>::type operator-(C lmat, Num val2) {
                        return lmat.map([&val2](T val1) {return val1 - val2;});
                    }
                template<typename Num>
                    friend typename std::enable_if<std::is_convertible<Num, T>::value, C>::type operator*(C lmat, Num val2) {
                        return lmat.map([&val2](T val1) {return val1 * val2;});
                    }
                template<class Mat>
                    friend typename std::enable_if<std::is_class<Mat>::value, Matrix<C, T>>::type operator*(C lmat, Mat rmat) {
                        if(lmat.cols() != rmat.rows() || lmat.rows() != rmat.cols()) {
                            exit(EXIT_FAILURE);
                        }
                        Matrix<C, T> mat(lmat.rows(), rmat.cols());
                        return mat.map([&lmat, &rmat] (T val, unsigned& x, unsigned& y) {
                                unsigned i;
                                for(i = 0; i < lmat.cols(); i++) {
                                    val += lmat.get(i, y) * lmat(x, i);
                                }
                                return val;
                                });
                    }
                template<typename Num>
                    friend typename std::enable_if<std::is_convertible<Num, T>::value, C>::type operator*(Num val2, C rmat) {
                        return rmat.map([&val2](T val1) {return val1 * val2;});
                    }
                unsigned rows() {
                    return this->_rows;
                }
                unsigned cols() {
                    return this->_cols;
                }
            private:
                std::vector<std::vector<T>> _matrix;
                const unsigned _rows, _cols;
                C& _chain() {
                    return static_cast<C&>(*this);
                }
                C& _forEach(std::function<void (T val, unsigned& x, unsigned& y)> callback) {
                    unsigned r, c;
                    for(r = 0; r < this->_rows; r++) {
                        for(c = 0; c < this->_cols; c++)
                            callback(this->_matrix[r][c], c, r);
                    }
                    return this->_chain();
                }
                C& _map(std::function<T (T val, unsigned& x, unsigned& y)> callback) {
                    return this->_forEach([this, callback](T val, unsigned& x, unsigned& y) -> T {return this->_matrix[y][x] = callback(val, x, y);});
                }
        };
}
