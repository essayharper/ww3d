#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <3ds.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <vshader_shbin.h>
#include <gfx/gfx.h>
#include <gfx/model.h>

// Helper function for loading a texture from memory
bool model::loadTexFromMem(C3D_Tex* tex, C3D_TexCube* cube, const void* data, size_t size) {
    Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, tex, cube, false);
    if (!t3x)
        return false;

    // Delete the t3x object since we don't need it
    Tex3DS_TextureFree(t3x);
    return true;
}
// Parse the .mdlf file, in the future I need to add bone support
model::model(std::string filename) {
    // Open the file
    std::ifstream mdlfFile(filename);

    while (std::getline(mdlfFile, readLine)) {
            // Get line prefix
            ss.clear();
            ss.str(readLine);
            ss >> prefix;
 
        if (prefix == "#") {
            // Do nothing
        } else if (prefix == "v") {
            ss >> pos.x >> pos.y >> pos.z >> comment >> tex.u >> tex.v >> comment >> nrm.x >> nrm.y >> nrm.z;
            mdlfVertices.push_back(pos.x);
            mdlfVertices.push_back(pos.y);
            mdlfVertices.push_back(pos.z);
            mdlfVertices.push_back(tex.u);
            mdlfVertices.push_back(tex.v);
            mdlfVertices.push_back(nrm.x);
            mdlfVertices.push_back(nrm.y);
            mdlfVertices.push_back(nrm.z);
        } else if (prefix == "i") {
            ss >> tempIdxA >> comment >> tempIdxB >> comment >> tempIdxC;
            mdlfIndices.push_back(tempIdxA);
            mdlfIndices.push_back(tempIdxB);
            mdlfIndices.push_back(tempIdxC);
        };
    };
   mdlfFile.close(); 

   // Transfer the vertex data from the vector to the VBO (Vertex Buffer Object)
   gfx::GFX::vbo_data = linearAlloc(sizeof(mdlfVertices));
   memcpy(gfx::GFX::vbo_data, mdlfVertices.data(), sizeof(mdlfVertices));

   // Transfer the indices from the vector to the IBO (Index Buffer Object)
   gfx::GFX::ibo_data = linearAlloc(sizeof(mdlfIndices));
   memcpy(gfx::GFX::ibo_data, mdlfIndices.data(), sizeof(mdlfIndices));

   if (!loadTexFromMem(&texture, &Cube, &Data, Size)) {
        svcBreak(USERBREAK_PANIC);
   };
   C3D_TexSetFilter(&texture, GPU_NEAREST, GPU_NEAREST);
};

void model::render(gfx::GFX &gfx) {
    // Configure attributes for use with the vertex shader
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // V0 = Position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // V1 = Texcoords
	AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // V2 = Normals

    // Configure buffers
	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, &gfx::GFX::vbo_data, sizeof(vertex), 3, 0x210);

	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
    C3D_TexBind(0, &texture);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_FRAGMENT_PRIMARY_COLOR);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);

    // Render Vertex Array, if the Index Array is empty
    if(mdlfIndices.empty()) {
        C3D_DrawArrays(GPU_TRIANGLES, 0, mdlfVertices.size());
    } else {
        C3D_DrawElements(GPU_TRIANGLES, mdlfIndices.size(), C3D_UNSIGNED_SHORT, &gfx::GFX::ibo_data);
    };
};

model::~model() {
    // Clear the vectors to free up some mem space before the object gets deleted
    mdlfIndices.clear();
    mdlfVertices.clear();

    // Free the texture
    C3D_TexDelete(&texture);

    // Free the Buffer Objects
    linearFree(gfx::GFX::vbo_data);
    linearFree(gfx::GFX::ibo_data);
};
