#include <thread>
#include "./Object.h"
using namespace Jim::Core;
using namespace std;

Jim::Core::Object::Object() {
    this->_active = &this->_local;
    this->_activeName = "local";
}

Jim::Core::Object::Object(buffer vertexBuffer) : Object() {
    this->_vertexBuffer = vertexBuffer;
}

void Jim::Core::Object::setVertexBuffer(buffer vertexBuffer) {
    lock_guard<mutex> lock(this->_mutex);
    this->_vertexBuffer = vertexBuffer;
}

Jim::Core::Object::buffer Jim::Core::Object::getVertexBuffer() {
    return this->_vertexBuffer;
}

void Jim::Core::Object::setActiveMatrix(string name) {
    lock_guard<mutex> lock(this->_mutex);
    if(name == "local") {
        this->_active = &this->_local;
    } else if(name == "world") {
        this->_active = &this->_world;
    } else {

    }
    this->_activeName = name;
}

string Jim::Core::Object::getActiveMatrixName() {
    return this->_activeName;
}
