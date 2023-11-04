#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <3ds.h>
#include <enums.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <vshader_shbin.h>
#include <gfx/model.h>
#include <gfx/gfx.h>

// Helper function for loading a texture from memory
static bool loadTexFromMem(C3D_Tex* texData, C3D_TexCube* cube, const void* data, size_t size) {
	Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, texData, cube, false);
	if (!t3x) {
		return false;
    };
    // Delete the t3x object since we don't need it
	Tex3DS_TextureFree(t3x);
	return true;
};

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
            mdlfPosition.push_back(pos.x);
            mdlfPosition.push_back(pos.y);
            mdlfPosition.push_back(pos.z);
            mdlfTexcoords.push_back(tex.u);
            mdlfTexcoords.push_back(tex.v);
            mdlfNormals.push_back(nrm.x);
            mdlfNormals.push_back(nrm.y);
            mdlfNormals.push_back(nrm.z);
        } else if (prefix == "i") {
            ss >> tempIdxA >> tempIdxB >> tempIdxC;
            mdlfIndices.push_back(tempIdxA);
            mdlfIndices.push_back(tempIdxB);
            mdlfIndices.push_back(tempIdxC);
        };
    };
   mdlfFile.close(); 
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
    if (!loadTexFromMem(&texData, &cube, &data, size)) {
        svcBreak(USERBREAK_PANIC);
    };
    C3D_TexBind(0, &texData);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, 0);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);

    // Render Vertex Array, if the Index Array is empty
    if(mdlfIndices.empty()) {
        C3D_DrawArrays(GPU_TRIANGLES, 0, mdlfVertices.size());
    } else {
        C3D_DrawElements(GPU_TRIANGLES, mdlfIndices.size(), C3D_UNSIGNED_SHORT, mdlfIndices.data());
    };
};

model::~model() {
    // Clear the vectors to free up some mem space before the object gets deleted
    mdlfPosition.clear();
    mdlfTexcoords.clear();
    mdlfNormals.clear();
    mdlfIndices.clear();
    mdlfVertices.clear();

    // Free the texture
    C3D_TexDelete(&texData);

    // Free the Vertex Buffer Object
    linearFree(gfx::GFX::vbo_data);
};
