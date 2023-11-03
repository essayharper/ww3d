#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <enums.h>
#include <citro3d.h>
#include <vshader_shbin.h>
#include <gfx/model.h>

model::model(std::string filename) {
    // Open the file
    std::ifstream mdlfFile(filename);

    while (std::getline(mdlfFile, model::readLine)) {
            // Get line prefix
            model::ss.clear();
            model::ss.str(readLine);
            model::ss >> model::prefix;
 
        if (model::prefix == "#") {
            // Do nothing
        } else if (prefix == "v") {
            ss >> pos.x >> pos.y >> pos.z >> comment >> tex.u >> tex.v >> comment >> nrm.x >> nrm.y >> nrm.z;
            model::mdlfPosition.push_back(pos.x);
            model::mdlfPosition.push_back(pos.y);
            model::mdlfPosition.push_back(pos.z);
            model::mdlfTexcoords.push_back(tex.u);
            model::mdlfTexcoords.push_back(tex.v);
            model::mdlfNormals.push_back(nrm.x);
            model::mdlfNormals.push_back(nrm.y);
            model::mdlfNormals.push_back(nrm.z);
        } else if (prefix == "i") {
            ss >> ind.a >> ind.b >> ind.c;
            model::mdlfIndices.push_back(ind.a);
            model::mdlfIndices.push_back(ind.b);
            model::mdlfIndices.push_back(ind.c);
        };
    };
   mdlfFile.close(); 
};

void model::render(gfx::GFX &gfx) {
    // Render Vertex Array, if the Index Array is empty
    if(model::mdlfIndices.empty()) {
        C3D_DrawArrays(GPU_TRIANGLES, 0, mdlfVertices.size());
    } else {
        C3D_DrawElements(GPU_TRIANGLES, model::mdlfIndices.size(), C3D_UNSIGNED_SHORT, model::mdlfIndices.data());
    };
};

model::~model() {
    // Clear the vectors to free up some mem space 
    mdlfPosition.clear();
    mdlfTexcoords.clear();
    mdlfNormals.clear();
    mdlfIndices.clear();
};
