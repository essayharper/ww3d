#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <enums.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <vshader_shbin.h>
#include <gfx/model.h>
#include <gfx/gfx.h>

// Helper function for loading a texture from memory
static bool loadTextureFromMem(C3D_Tex* texture, C3D_TexCube* cube, const void* data, size_t size) {
	Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, texture, cube, false);
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

    while (std::getline(mdlfFile, model::readLine)) {
            // Get line prefix
            model::ss.clear();
            model::ss.str(readLine);
            model::ss >> model::prefix;
 
        if (model::prefix == "#") {
            // Do nothing
        } else if (model::prefix == "v") {
            ss >> pos.x >> pos.y >> pos.z >> comment >> tex.u >> tex.v >> comment >> nrm.x >> nrm.y >> nrm.z;
            model::mdlfPosition.push_back(pos.x);
            model::mdlfPosition.push_back(pos.y);
            model::mdlfPosition.push_back(pos.z);
            model::mdlfTexcoords.push_back(tex.u);
            model::mdlfTexcoords.push_back(tex.v);
            model::mdlfNormals.push_back(nrm.x);
            model::mdlfNormals.push_back(nrm.y);
            model::mdlfNormals.push_back(nrm.z);
        } else if (model::prefix == "i") {
            ss >> model::tempIdxA >> model::tempIdxB >> model::tempIdxC;
            model::mdlfIndices.push_back(model::tempIdxA);
            model::mdlfIndices.push_back(model::tempIdxB);
            model::mdlfIndices.push_back(model::tempIdxC);
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
    C3D_TexBind(0, &gfx::GFX::texture);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);

    // Render Vertex Array, if the Index Array is empty
    if(model::mdlfIndices.empty()) {
        C3D_DrawArrays(GPU_TRIANGLES, 0, mdlfVertices.size());
    } else {
        C3D_DrawElements(GPU_TRIANGLES, model::mdlfIndices.size(), C3D_UNSIGNED_SHORT, model::mdlfIndices.data());
    };
};

model::~model() {
    // Clear the vectors to free up some mem space before the object gets deleted
    mdlfPosition.clear();
    mdlfTexcoords.clear();
    mdlfNormals.clear();
    mdlfIndices.clear();
    mdlfVertices.clear();
};
