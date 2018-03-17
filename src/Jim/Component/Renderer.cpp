#include "./Renderer.h"
#include <ncurses.h>

Jim::Component::Renderer::Renderer() {
    initscr();
    curs_set(0);
    noecho();
    timeout(0);
    clear();
    this->clear();
}

Jim::Component::Renderer::~Renderer() {
    endwin();
}

void Jim::Component::Renderer::clear() {
    this->_renderedObjects = {};
    this->_pixels = {};
    xyz screenSize = this->getScreenSize();
    for(unit x = 0; x < screenSize.x; x++) {
        for(unit y = 0; y < screenSize.y; y++) {
            this->_pixels.push_back({
                    .object = 0,
                    .position = {.x = x, .y = y, .z = 0}});
        }
    }
}

void Jim::Component::Renderer::addObject(Object* object) {
    this->_objects.push_back(object);
}

xyz Jim::Component::Renderer::getScreenSize() {
    xyz res;
    getmaxyx(stdscr,res.y,res.x);
    return res;
}

void Jim::Component::Renderer::setCamera(Camera* camera) {
    this->_camera = camera;
}

void Jim::Component::Renderer::render() {
    int screenX, screenY;
    getmaxyx(stdscr, screenY, screenX);
    this->renderObjects();
    wclear(stdscr);
    for(auto& obj : this->_renderedObjects) {
        xyz position;
        unsigned i = 0;
        for(auto& index : obj.getVertexBuffer()) {
            i++;
            switch(i) {
                case 1:
                    position.x = screenX / 2 + index;
                    break;
                case 2:
                    position.y = screenY / 2 + index;
                    break;
                case 3:
                    position.z = index;
                    i = 0;
                    mvaddch(position.y, position.x, 'x');
                    break;
            }
        }
    }
    wrefresh(stdscr);
}

void Jim::Component::Renderer::renderObjects() {
    this->_renderedObjects = {};
    for(auto& object : this->_objects) {
        buffer vBuf = object->getVertexBuffer();
        buffer vRenBuf = {};    //Rendered buffer
        unsigned i = 0;
        xyz actual = {.x = 0, .y = 0, .z = 0};
        matrix m = object->getMatrix();
        matrix p = this->_camera->getProjectionMatrix();
        for(auto& index : vBuf) {
            i++;
            switch(i) {
                case 1:
                    actual.x = index;
                    break;
                case 2:
                    actual.y = index;
                    break;
                case 3:
                    actual.z = index;
                    matrix vertex(1,4);
                    vertex.set(0,0,actual.x).set(0,1,actual.y).set(0,2,actual.z).set(0,3,1);
                    vertex = p * (m * vertex);
                    vertex.set(0,0, vertex.get(0,0) * vertex.get(0,3)).set(0,1, vertex.get(0,1) * vertex.get(0,3));
                    vRenBuf.push_back(vertex.get(0,0));
                    vRenBuf.push_back(vertex.get(0,1));
                    vRenBuf.push_back(vertex.get(0,2));
                    actual = {.x = 0, .y = 0, .z = 0};
                    i = 0;
                    break;
            }
            Object obj;
            obj.setVertexBuffer(vRenBuf);
            this->_renderedObjects.push_back(obj);
        }
    }
}
