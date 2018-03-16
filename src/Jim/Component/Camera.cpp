#include "./Camera.h"

Jim::Component::Camera::Camera() : Object() {
    this->_fov = 90;
}

unit Jim::Component::Camera::getFOV() {
    return this->_fov;
}

void Jim::Component::Camera::setFOV(unit fov) {
    this->_fov = fov;
}
