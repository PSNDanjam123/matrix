#pragma once
#include "./Jim/Core/Matrix.h"
using namespace Jim::Core;

#define PI 3.141592

namespace Ship {
    extern bool running;   //App status

    typedef struct object {
        //vertices
        Matrix<float> x = {{-1},{-1},{ 0},{ 1}};
        Matrix<float> y = {{ 0},{ 1},{ 0},{ 1}};
        Matrix<float> z = {{ 1},{-1},{ 0},{ 1}};

        //matrices
        Matrix<float> matrix = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        };
        Matrix<float> translation = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        };
        Matrix<float> rotation = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        };
        Matrix<float> scale = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        };
    } object;

    typedef struct ship {
        Ship::object    object;
        Matrix<float>   force = {{0},{0},{0},{0}};
        float           thrust = 0.05;
        float           spin = 0;
        bool            dampener = false;
    } ship;

    //Objects
    extern ship USS_Ent;

    //Methods
    void init();
    void rotate(object& obj, float deg);
    void translate(object& obj, float x, float y, float z);
    void scale(object& scale, float x, float y, float z);
    float degToRad(float deg);
    float radToDeg(float rad);

    void threadRender();
    void threadSimulate();
    void threadInput();
}
