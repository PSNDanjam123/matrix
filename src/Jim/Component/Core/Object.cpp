#include "../../Core/Types.h"
#include "../../Core/Math.h"
#include "./Object.h"
#include <cmath>

using namespace Jim::Core::Math;
using namespace Jim::Core::Types;
using namespace std;

Jim::Component::Core::Object::Object() {
    this->_orientation = matrix(4,4).identity();
    this->setScale(1,1,1);
    this->setRotation(0,0,0);
    this->setPosition(0,0,0);
    this->updateOrientation();
}

rBuffer Jim::Component::Core::Object::getVertexBuffer() {
    return this->_vertexBuffer;
}

void Jim::Component::Core::Object::setVertexBuffer(list1d list) {
    buffer buf;
    for(auto& value : list) {
        buf.push_back(value);
    }
    return this->setVertexBuffer(buf);
}

void Jim::Component::Core::Object::setVertexBuffer(buffer buf) {
    this->_vertexBuffer = buf;
}

xyz Jim::Component::Core::Object::getPosition() {
    return this->_position;
}

xyz Jim::Component::Core::Object::getRotation() {
    return this->_rotation;
}

xyz Jim::Component::Core::Object::getScale() {
    return this->_scale;
}

void Jim::Component::Core::Object::setPosition(unit x, unit y, unit z) {
    this->_position = {.x = x, .y = y, .z = z};
}

void Jim::Component::Core::Object::setRotation(unit x, unit y, unit z) {
    x = fmod(360 + x, 360);
    y = fmod(360 + y, 360);
    z = fmod(360 + z, 360);
    this->_rotation = {.x = x, .y = y, .z = z};
}

void Jim::Component::Core::Object::setScale(unit x, unit y, unit z) {
    this->_scale = {.x = x, .y = y, .z = z};
}

void Jim::Component::Core::Object::translate(unit x, unit y, unit z) {
    this->setPosition(this->_position.x + x, this->_position.y + y, this->_position.z + z);
}

void Jim::Component::Core::Object::transform(unit x, unit y, unit z) {
    this->setScale(this->_scale.x + x, this->_scale.y + y, this->_scale.z + z);
}

void Jim::Component::Core::Object::scale(unit x) {
    this->transform(x,x,x);
}

void Jim::Component::Core::Object::rotate(unit x, unit y, unit z) {
    this->setRotation(this->_rotation.x + x, this->_rotation.y + y, this->_rotation.z + z);
}

matrix Jim::Component::Core::Object::getTranslationMatrix() {
    matrix m(4,4);
    m = m.identity();
    m.set(3,0, this->_position.x).set(3,1, this->_position.y).set(3,2, this->_position.z);
    return m;
}

matrix Jim::Component::Core::Object::getTransformationMatrix() {
    matrix m(4,4);
    m = m.identity();
    m.set(0,0, this->_scale.x).set(1,1, this->_scale.y).set(2,2, this->_scale.z);
    return m;
}

matrix Jim::Component::Core::Object::getRotationXMatrix() {
    unit rad = degToRad(this->_nextRotation.x - this->_rotation.x);
    unit cos = std::cos(rad);
    unit sin = std::sin(rad);
    matrix m(4,4);
    m = m.identity();
    m.set(1,1, cos).set(2,1, -sin).set(1,2, sin).set(2,2, cos);
    return m;
}

matrix Jim::Component::Core::Object::getRotationYMatrix() {
    unit rad = degToRad(this->_nextRotation.y - this->_rotation.y);
    unit cos = std::cos(rad);
    unit sin = std::sin(rad);
    matrix m(4,4);
    m = m.identity();
    m.set(0,0, cos).set(2,0, sin).set(0,2, -sin).set(2,2, cos);
    return m;
}

matrix Jim::Component::Core::Object::getRotationZMatrix() {
    unit rad = degToRad(this->_nextRotation.y - this->_rotation.z);
    unit cos = std::cos(rad);
    unit sin = std::sin(rad);
    matrix m(4,4);
    m = m.identity();
    m.set(0,0, cos).set(1,0, -sin).set(0,1, sin).set(1,1, cos);
    return m;
}

matrix Jim::Component::Core::Object::getRotationMatrix() {
    matrix x = this->getRotationXMatrix();
    matrix y = this->getRotationYMatrix();
    matrix z = this->getRotationZMatrix();
    return z * y * x;
}

matrix Jim::Component::Core::Object::getMatrix() {
    matrix t = this->getTranslationMatrix();
    matrix s = this->getTransformationMatrix();
    matrix r = this->getRotationMatrix();
    return s * t * r;
}

void Jim::Component::Core::Object::updateOrientation() {
    matrix rot = this->getRotationMatrix();
    this->_orientation = rot * this->_orientation;
    this->_rotation = this->_nextRotation;
    this->_nextRotation = this->_rotation;
}

matrix Jim::Component::Core::Object::getOrientation() {
    return this->_orientation;
}
