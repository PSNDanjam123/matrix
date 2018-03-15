#include <iostream>
#include <thread>
#include "./World.h"
using namespace std;

Jim::Core::World::World(unsigned w, unsigned h, unsigned d) {
    this->_width = w;
    this->_height = h;
    this->_depth = d;
}

void Jim::Core::World::tick() {
    lock_guard<mutex> lock(this->_mutex);
    struct matrixGroup {
        Object::matrix translation;
        Object::matrix transformation;
        Object::matrix rotation;
    };
    for(auto object : this->objects) {
        //Extract object vertices
        vector<Object::matrix> matrices = object->getVertices();

        //Extract matrices
        object->setActiveMatrix("local");
        struct matrixGroup local = {
            .translation = object->getTranslation(),
            .transformation = object->getTransformation(),
            .rotation = object->getRotation()
        };
        object->setActiveMatrix("world");
        struct matrixGroup world = {
            .translation = object->getTranslation(),
            .transformation = object->getTransformation(),
            .rotation = object->getRotation()
        };
    }
}
