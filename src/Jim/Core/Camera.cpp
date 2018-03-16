#include <cmath>
#include "./Camera.h"
using namespace std;

Jim::Core::Camera::Camera() {
    this->_fov = .9;
    this->_pos = {{0.0},{0.0},{0.0},{0.0}};
}

void Jim::Core::Camera::translate(float x, float y, float z) {
    this->_pos.set(0,0, this->_pos.get(0,0) + x);
    this->_pos.set(0,1, this->_pos.get(0,1) + y);
    this->_pos.set(0,2, this->_pos.get(0,2) + z);
}

void Jim::Core::Camera::setFOV(float fov) {
    this->_fov = fov;
}

float Jim::Core::Camera::getFOV() {
    return this->_fov;
}

float Jim::Core::Camera::FOVToZ(float fov) {
    float pi = 3.141592;
    fov = fov / 180 * pi;

    return 1 / tan(fov/2);
}

float Jim::Core::Camera::ZToFOV(float z) {
    return 2 * atan(1/z);
}

std::vector<std::vector<Jim::Core::Object::matrix>> Jim::Core::Camera::render(std::vector<std::vector<Object::matrix>>& objects) {

    double z = this->FOVToZ(this->_fov);

    Object::matrix e = {{0.0},{0.0},{z},{0.0}};

    Object::matrix m = {
        {1.0, 0.0, -(e.get(0,0)/e.get(0,2)), 0.0},
        {0.0, 1.0, -(e.get(0,1)/e.get(0,2)), 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, -(1/e.get(0,2)), 1.0}};

    for(auto& object : objects) {
        for(auto& vertex : object) {
            vertex = vertex - this->_pos;
            vertex = m * vertex;
            vertex.set(0,0, vertex.get(0,0) / vertex.get(0,3));
            vertex.set(0,1, vertex.get(0,1) / vertex.get(0,3));
        }
    }
    return objects;
}
