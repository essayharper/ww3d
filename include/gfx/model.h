#ifndef WIND_WAKER_3D_MODEL_H
#define WIND_WAKER_3D_MODEL_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <citro3d.h>

#include "gfx.h"
#include "engine/vertex.h"

class model {
    public:
    model(std::string filename);
    ~model();

    void render(gfx::GFX &gfx);

    std::string readLine;
    std::stringstream ss;
    std::string prefix;
    std::string comment;

    vertex::position pos;
    vertex::texcoords tex;
    vertex::normals nrm;
    vertex::color clr;

    unsigned int tempIdxA;
    unsigned int tempIdxB;
    unsigned int tempIdxC;

    unsigned int maxIndices;

    std::vector<float>mdlfVertices;
    std::vector<unsigned int> mdlfIndices;

    C3D_Tex texture;
    C3D_TexCube Cube; 
    const void* Data;
    size_t Size;
    bool loadTexFromMem(C3D_Tex* tex, C3D_TexCube* cube, const void* data, size_t size);
};
#endif
