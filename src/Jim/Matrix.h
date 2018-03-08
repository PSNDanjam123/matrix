#pragma once
#include "./Matrix/Mat.h"
#include "./Matrix/Mat3.h"
#include "./Matrix/Mat4.h"

namespace Jim::Matrix {
    typedef Mat<int> Mati;
    typedef Mat<float> Matf;
    typedef Mat<long> Matl;
    typedef Mat3<int> Mat3i;
    typedef Mat3<float> Mat3f;
    typedef Mat3<long> Mat3l;
    typedef Mat4<int> Mat4i;
    typedef Mat4<float> Mat4f;
    typedef Mat4<long> Mat4l;
}
