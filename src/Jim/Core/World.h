#pragma once
#include <vector>
#include <mutex>
#include "./Object.h"
#include "./Camera.h"

namespace Jim::Core {
    class World {
        public:
            World(unsigned w, unsigned h, unsigned d);
            std::vector<Object*> objects;
            Camera camera;
            void tick();
        private:
            unsigned _width;
            unsigned _height;
            unsigned _depth;
            std::mutex _mutex;
    };
}
