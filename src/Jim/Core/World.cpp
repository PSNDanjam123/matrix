#include <iostream>
#include <thread>
#include "./World.h"
#include <ncurses.h>
using namespace std;

Jim::Core::World::World(unsigned w, unsigned h, unsigned d) {
    this->_width = w;
    this->_height = h;
    this->_depth = d;
}

void Jim::Core::World::tick() {
    lock_guard<mutex> lock(this->_mutex);
    vector<vector<Object::matrix>> objects;

    for(auto object : this->objects) {
        //Extract object vertices
        vector<Object::matrix> vertices = object->getVertices();
        
        //Determine matrix
        object->setActiveMatrix("local");
        Object::matrix local = object->getTransformation() * object->getTranslation() * object->getRotation();

        object->setActiveMatrix("world");
        Object::matrix world = object->getTransformation() * object->getTranslation() * object->getRotation();

        Object::matrix matrix = local * world;

        //Apply matrix to vertices
        for(auto& vertex : vertices) {
            vertex = matrix * vertex;
        }

        //Add rendered vertices to objects
        objects.push_back(vertices);
    }
    objects = this->camera.render(objects);

    //demo
    int world_x, world_y;
    getmaxyx(stdscr, world_y, world_x);
    for(auto& object : objects) {
        for(auto& vertex : object) {
            int x = (world_x / 2) - vertex.get(0,0);
            int y = (world_y / 2) - vertex.get(0,1);
            mvaddch(y,x,'x');
        }
    }

}
