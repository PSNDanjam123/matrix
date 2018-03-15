#pragma once
#include <string>
#include <mutex>
#include <cmath>
#include "./Matrix.h"

#define PI 3.141592

namespace Jim::Core {
    class Object {
        public:
            typedef double unit; //The unit used for all objects
            typedef std::vector<unit> buffer;
            typedef Matrix<unit> matrix;
            Object();
            Object(buffer);
            template <typename T>
                Object(std::initializer_list<T> list) : Object() {
                    for(auto& item : list) {
                        this->_vertexBuffer.push_back(item);
                    }
                }
            template <typename T>
                unit degToRad(T deg) {
                    return deg / 180 * PI;
                }
            template <typename T>
                unit radToDeg(T rad) {
                    return rad * 180 / PI;
                }
            void setVertexBuffer(buffer);
            buffer getVertexBuffer();
            void setActiveMatrix(std::string name);
            std::string getActiveMatrixName();
            template <typename T>
                void translate(T x, T y, T z) {
                    std::lock_guard<std::mutex> lock(this->_mutex);
                    Matrix<unit> m = {
                        {1.0f, 0.0f, 0.0f,    x},
                        {0.0f, 1.0f, 0.0f,    y},
                        {0.0f, 0.0f, 1.0f,    z},
                        {0.0f, 0.0f, 0.0f, 1.0f}};
                    this->_active->translation = m * this->_active->translation;
                }
            template <typename T>
                void rotateX(T deg) {
                    std::lock_guard<std::mutex> lock(this->_mutex);
                    unit rad = this->degToRad(deg);
                    unit cos = std::cos(rad);
                    unit sin = std::sin(rad);
                    Matrix<unit> m = {
                        {1.0, 0.0, 0.0, 0.0},
                        {0.0,  cos, -sin, 0.0},
                        {0.0, sin, cos, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
                    this->_active->rotation = m * this->_active->rotation;
                }
            template <typename T>
                void rotateY(T deg) {
                    std::lock_guard<std::mutex> lock(this->_mutex);
                    unit rad = this->degToRad(deg);
                    unit cos = std::cos(rad);
                    unit sin = std::sin(rad);
                    Matrix<unit> m = {
                        {cos, 0.0, sin, 0.0},
                        {0.0,  1.0, 0.0, 0.0},
                        {-sin, 0.0, cos, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
                    this->_active->rotation = m * this->_active->rotation;
                }
            template <typename T>
                void rotateZ(T deg) {
                    std::lock_guard<std::mutex> lock(this->_mutex);
                    unit rad = this->degToRad(deg);
                    unit cos = std::cos(rad);
                    unit sin = std::sin(rad);
                    Matrix<unit> m = {
                        {cos, -sin, 0.0, 0.0},
                        {sin,  cos, 0.0, 0.0},
                        {0.0, 0.0, 1.0, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
                    this->_active->rotation = m * this->_active->rotation;
                }
            template <typename T>
                void transform(T x, T y, T z) {
                    std::lock_guard<std::mutex> lock(this->_mutex);
                    Matrix<unit> m = {
                        {x, 0.0, 0.0, 0.0},
                        {0.0, y, 0.0, 0.0},
                        {0.0, 0.0, z, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
                    this->_active->transformation = m * this->_active->transformation;
                }
        private:
            buffer _vertexBuffer;
            typedef struct matrixGroup {    //Sperate all for combining later
                matrix translation = matrix(4,4).identity();
                matrix rotation = matrix(4,4).identity();
                matrix transformation = matrix(4,4).identity();
            } matrixGroup;
            matrixGroup* _active;
            std::string _activeName;
            matrixGroup _local;
            matrixGroup _world;
            std::mutex _mutex;
    };
}
