#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <functional>

namespace Jim::Matrix::Core {
    template <class C, typename T> class Matrix {
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
            virtual C clone() {
                return this->_chain();
            }
            virtual std::string str() {
                std::stringstream output;
                this->_loop([this, &output](T val, unsigned x, unsigned) -> T {
                        output << val << '\t';
                        if(x == this->_cols - 1)
                        output << '\n';});
                return output.str();
            }
            virtual T& operator() (unsigned x, unsigned y) {
                return this->_matrix[y][x];
            }
            template <class Mat> typename std::enable_if<std::is_class<Mat>::value, bool>::type operator==(Mat& mat) {
                bool result = true;
                mat.map([this, &result](T val, unsigned x, unsigned y) {
                        if(this->_matrix[y][x] != val) {
                            result = false;
                        }
                        return val;
                        });
                return result;
            }
            template <class Mat> typename std::enable_if<std::is_class<Mat>::value, bool>::type operator!=(Mat& mat) {
                bool result = false;
                mat.map([this, &result](T val, unsigned x, unsigned y) {
                        if(this->_matrix[y][x] != val) {
                        result = true;
                        }
                        return val;
                        });
                return result;
            }
            template <class Mat> typename std::enable_if<std::is_class<Mat>::value, C&>::type operator+= (Mat mat) {
                if(this->_cols != mat.cols() || this->_rows != mat.rows()) {
                    exit(EXIT_FAILURE);
                }
                return this->map([&mat](float val, unsigned x, unsigned y) {return val + mat(x,y);});
            }
            template <typename Num> typename std::enable_if<std::is_convertible<Num, T>::value, C&>::type operator+= (Num val2) {
                return this->map([&val2](float val) {return val + val2;});
            }
            template <class Mat> typename std::enable_if<std::is_class<Mat>::value, C&>::type operator-= (Mat mat) {
                if(this->_cols != mat.cols() || this->_rows != mat.rows()) {
                    exit(EXIT_FAILURE);
                }
                return this->map([&mat](float val, unsigned x, unsigned y) {return val - mat(x,y);});
            }
            template <typename Num> typename std::enable_if<std::is_convertible<Num, T>::value, C&>::type operator-= (Num val2) {
                return this->map([&val2](float val) {return val - val2;});
            }
            template<class Mat> friend typename std::enable_if<std::is_class<Mat>::value, C>::type operator+(C lmat, Mat rmat) {
                C mat = lmat.clone();
                mat.map([&rmat](T val, unsigned x, unsigned y) {return val + rmat.get(x, y);});
                return mat;
            }
            template<typename Num> friend typename std::enable_if<std::is_convertible<Num, T>::value, C>::type operator+(C lmat, Num val2) {
                C mat = lmat.clone();
                mat.map([&val2](T val1, unsigned, unsigned) {return val1 + val2;});
                return mat;
            }
            unsigned rows() {
                return this->_rows;
            }
            unsigned cols() {
                return this->_cols;
            }
        private:
            std::vector<std::vector<T>> _matrix;
            const unsigned _rows;   //y
            const unsigned _cols;   //x
            C& _chain() {
                return static_cast<C&>(*this);
            }
            void _loop(std::function<void (T val, unsigned x, unsigned y)> callback) {
                unsigned r, c;
                for(r = 0; r < this->_rows; r++) {
                    for(c = 0; c < this->_cols; c++) {
                        callback(this->_matrix[r][c], c, r);
                    }
                }
            }
            void _map(std::function<T (T val, unsigned x, unsigned y)> callback) {
                this->_loop([this, callback](T val, unsigned x, unsigned y) -> T {return this->_matrix[y][x] = callback(val, x, y);});
            }
    };
}
