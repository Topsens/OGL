#pragma once

#include "VectorX.h"
#include <cstdint>

typedef VXNS::Vector<3, uint32_t> Element;
typedef VXNS::Vector<3, float>    Vertex;
typedef VXNS::Vector<3, float>    Normal;
typedef VXNS::Vector<4, float>    Color;
typedef VXNS::Vector<2, float>    Coordinate;

template<typename T, size_t N>
char(&_ArraySizeHelper(T(&)[N]))[N];
#define COUNTOF(arr)(sizeof( _ArraySizeHelper(arr)))