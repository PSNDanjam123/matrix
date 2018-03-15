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
    for(auto object : this->objects) {
        vector<Object::matrix> matrices = object->getVertices();
    }
}
