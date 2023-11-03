#ifndef WIND_WAKER_3D_MODEL_H
#define WIND_WAKER_3D_MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "gfx.h"
#include "engine/vertex.h"
#include "engine/vector.h"

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

    std::vector<vec3> mdlfPosition;
    std::vector<vec2> mdlfTexcoords;
    std::vector<vec3> mdlfNormals;
    std::vector<float>mdlfVertices;
    std::vector<idx> mdlfIndices;
};
#endif