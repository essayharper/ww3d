// Created by Lollio64 1/11/23
#ifndef WIND_WAKER_3D_VERTEX_H
#define WIND_WAKER_3D_VERTEX_H

#include <iostream>
#include <citro3d.h>

class vertex {
    public:
    struct position {
        float x, y, z;
    };

    struct texcoords {
        float uvx, uvy;
    };

    struct normals {
        float nx, ny, nz;
    };

    struct color {
        float r, g, b;
    };
};
#endif
