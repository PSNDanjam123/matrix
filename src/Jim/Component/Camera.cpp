#include <cmath>
#include "./Camera.h"
#include "../Core/Math.h"

using namespace Jim::Core::Math;
using namespace std;

Jim::Component::Camera::Camera() {
    this->setFOV(90);
}

unit Jim::Component::Camera::getFOV() {
    xyz viewerPos = this->_viewer.getPosition();
    unit z = viewerPos.z;
    return 100 * radToDeg(2 * atan(1/z));
}

void Jim::Component::Camera::setFOV(unit fov) {
    unit f = degToRad(fov) / 100;
    unit z = 1 / tan(f/2);
    xyz viewerPos = this->_viewer.getPosition();
    this->_viewer.setPosition(viewerPos.x, viewerPos.y, z);
}

matrix Jim::Component::Camera::getProjectionMatrix() {
    matrix m(4,4);
    m = m.identity();
    xyz viewerPos = this->_viewer.getPosition();
    m.set(2,0,-(viewerPos.x/viewerPos.z)).set(2,1, -(viewerPos.y/viewerPos.z)).set(2,3, -(1/viewerPos.z));
    return m;
}
