// Created by Lollio64 1/11/23
#ifndef WIND_WAKER_3D_VECTOR_H
#define WIND_WAKER_3D_VECTOR_H

#include <iostream>
#include <citro3d.h>

struct vec2 {
    float x;
    float y;

    C3D_FVec vec2 = FVec4_New(0.0f, 0.0f, y, x);
};

struct vec3 {
    float x;
    float y;
    float z;

    C3D_FVec vec3 = FVec4_New(0.0f, z, y, x);
}

#endif