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
                this->map([this, &output](T val, unsigned x, unsigned) -> T {
                        output << val << '\t';
                        if(x == this->_cols - 1)
                        output << '\n';
                        return val;});
                return output.str();
            }
            virtual T& operator() (unsigned x, unsigned y) {
                return this->_matrix[y][x];
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
