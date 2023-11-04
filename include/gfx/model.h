#ifndef WIND_WAKER_3D_MODEL_H
#define WIND_WAKER_3D_MODEL_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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
    idx ind;

    unsigned int indices;

    std::vector<float> mdlfPosition;
    std::vector<float> mdlfTexcoords;
    std::vector<float> mdlfNormals;
    std::vector<float>mdlfVertices;
    std::vector<unsigned int> mdlfIndices;
};
#endif
