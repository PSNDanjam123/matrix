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

vector<Jim::Core::Object::matrix> Jim::Core::Object::getVertices() {
    vector<matrix> matrices;
    unsigned i = 0;
    unit x = 0, y = 0, z = 0;
    for(auto index : this->_vertexBuffer) {
        i++;
        switch(i) {
            case 1:
                x = index;
                break;
            case 2:
                y = index;
                break;
            case 3:
                z = index;
                i = 0;
                matrices.push_back({{x},{y},{z},{1.0}});
                x = 0;
                y = 0;
                z = 0;
                break;
        }
    }
    return matrices;
}

Jim::Core::Object::matrix Jim::Core::Object::getTranslation() {
    return this->_active->translation;
}

Jim::Core::Object::matrix Jim::Core::Object::getRotation() {
    return this->_active->rotation;
}

Jim::Core::Object::matrix Jim::Core::Object::getTransformation() {
    return this->_active->transformation;
}
