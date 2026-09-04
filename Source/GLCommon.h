#pragma once

#include "VectorX.h"
#include <cstdint>

#ifdef VECTORX_NS
    #define VXNS VECTORX_NS
#else
    #define VXNS
#endif

typedef VXNS::Vector<3, uint32_t> Element;
typedef VXNS::Vector<3, float>    Vertex;
typedef VXNS::Vector<3, float>    Normal;
typedef VXNS::Vector<4, float>    Color;
typedef VXNS::Vector<2, float>    Coordinate;

#undef VXNS

template<typename T, size_t N>
char(&_ArraySizeHelper(T(&)[N]))[N];
#define COUNTOF(arr)(sizeof( _ArraySizeHelper(arr)))