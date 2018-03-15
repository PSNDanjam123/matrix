#include <cmath>
#include "./Camera.h"
using namespace std;

Jim::Core::Camera::Camera() {
    this->_fov = 75;
}

void Jim::Core::Camera::setFOV(float fov) {
    this->_fov = fov;
}

float Jim::Core::Camera::getFOV() {
    return this->_fov;
}

float Jim::Core::Camera::FOVToZ(float fov) {
    return 1 / tan(fov/2);
}

float Jim::Core::Camera::ZToFOV(float z) {
    return 2 * atan(1/z);
}

std::vector<std::vector<Jim::Core::Object::matrix>> Jim::Core::Camera::render(std::vector<std::vector<Object::matrix>>& objects) {

    double z = this->FOVToZ(this->_fov);

    Object::matrix c = {{0.0},{0.0}, {-1.0}, {1.0}};

    Object::matrix e = {{1.0},{1.0},{z},{1.0}};

    Object::matrix m = {
        {1.0, 0.0, -(e.get(0,0)/e.get(0,2)), 0.0},
        {0.0, 1.0, -(e.get(0,1)/e.get(0,2)), 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, -(e.get(0,2)/e.get(0,2)), 1.0}};

    for(auto& object : objects) {
        for(auto& vertex : object) {
            vertex = vertex - c;
            vertex = m * vertex;
        }
    }
    return objects;
}
