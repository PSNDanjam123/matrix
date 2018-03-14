#include "./Object.h"

Jim::Core::Object::Object() {
    this->_matrix = &this->_localMatrix;
    this->_localMatrix.resize(4,4);
    this->_worldMatrix.resize(4,4);
    this->_localMatrix = this->_localMatrix.identity();
    this->_worldMatrix = this->_worldMatrix.identity();
}

void Jim::Core::Object::translate(float x, float y, float z) {
    matrix m = {
        {1.0f, 0.0f, 0.0f,    x},
        {0.0f, 1.0f, 0.0f,    y},
        {0.0f, 0.0f, 1.0f,    z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    *this->_matrix = m * (*this->_matrix);
}

void Jim::Core::Object::scale(float amount) {
    this->scale(amount, amount, amount);
}

void Jim::Core::Object::scale(float x, float y, float z) {
    matrix m = {
        {x   , 0.0f, 0.0f, 0.0f},
        {0.0f,    y, 0.0f, 0.0f},
        {0.0f, 0.0f,    z, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    *this->_matrix = m * (*this->_matrix);
}
