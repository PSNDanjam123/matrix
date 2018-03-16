#pragma once
#include "./Matrix.h"
#include <vector>
#include <mutex>

using namespace std;

namespace Jim::Core::Types {

    //Number system
    typedef double          unit;
    typedef unit*           pUnit;
    typedef unit&           rUnit;

    //Coords
    typedef struct xyz {
        unit x = 0;
        unit y = 0;
        unit z = 0;
    }                       xyz;
    typedef xyz*            pXyz;
    typedef xyz&            rXyz;

    //Matrices
    typedef Matrix<unit>    matrix;
    typedef matrix*         pMatrix;
    typedef matrix&         rMatrix;

    //Buffers
    typedef vector<unit>    buffer;
    typedef buffer*         pBuffer;
    typedef buffer&         rBuffer;

    //Lists
    typedef initializer_list<unit> list1d;
    typedef list1d*         pList1d;
    typedef list1d&         rList1d;
    typedef initializer_list<initializer_list<unit>> list2d;
    typedef list2d*         pList2d;
    typedef list2d&         rList2d;

    //Mutex
    typedef lock_guard<mutex>   threadLock;
    typedef threadLock*         pThreadLock;
    typedef threadLock&         rThreadLock;

}
