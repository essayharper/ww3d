#ifndef WIND_WAKER_3D_VECTOR_H
#define WIND_WAKER_3D_VECTOR_H

#include <iostream>

struct vec2 {
    float x;
    float y;
}; // 2D Vector

struct vec3 {
    float x;
    float y;
    float z;
}; // 3D Vector

struct idx {
    unsigned int a;
    unsigned int b;
    unsigned int c;
}; // Triangle built from indices a, b, c
#endif