#include "mesh.h"

// Load the 3D model
mesh::mesh(std::string path) {
    FILE* fd = fopen(path.c_str(), "r");
	if(fd == NULL) return;

	vertex v;
	while(true) {
		char line[128];

		int res = fscanf(fd, "%s", line);
		if(res == EOF) return;

		if(strcmp(line, "v") == 0) {
			fscanf(fd, "%f%f%f %f%f %f%f%f\n", &v.position.x, &v.position.y, &v.position.z, &v.uv.x, &v.uv.y, &v.normal.x, &v.normal.y, &v.normal.z);
			vertices.push_back(v);
		} else if(strcmp(line, "i") == 0) {
			index i[3];
			fscanf(fd, "%hu%hu%hu\n", &i[0], &i[1], &i[2]);
			indices.push_back(i[0]);
			indices.push_back(i[1]);
			indices.push_back(i[2]);
		} else {
			char comment[128];
			fgets(comment, 128, fd);
		};
	};

	fclose(fd);

	position = vec3(0.f, 0.f, 0.0f);
    rotation = vec3(0.f, 0.f, 0.f);
    scale = vec3(1.f, 1.f, 1.f);

	// Allocate a Vertex Buffer Object
	vbo_data = (vertex*)linearAlloc(sizeof(vertices[0]) * vertices.size());
	memcpy(vbo_data, vertices.data(), sizeof(vertices[0]) * vertices.size());

	// Allocate a Index Buffer Object
	ibo_data = (index*)linearAlloc(sizeof(indices[0]) * indices.size());
	memcpy(ibo_data, indices.data(), sizeof(indices[0]) * indices.size());
};

// Draw the 3D model
void mesh::Draw(player &ply) {
	// Update Position, Rotation and Scale in World Space
	Mtx_Identity(&modelMtx);
	Mtx_Translate(&modelMtx, position.x, position.y, position.z, true);
	Mtx_RotateX(&modelMtx, rotation.x, true);
	Mtx_RotateY(&modelMtx, rotation.y, true);
	Mtx_RotateZ(&modelMtx, rotation.z, true);
	Mtx_Scale(&modelMtx, scale.x, scale.y, scale.z);

	// Go from World Space to Camera Space and update the modelView uniform
	Mtx_Multiply(&modelMtx, &ply.GetViewMtx(), &modelMtx);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, gfx::uLoc_modelView, &modelMtx);

    // Reinitialize the Vertex Attribute Info for drawing
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attrInfo);
    AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
    AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // v1=uv
    AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // v2=normal
	C3D_SetAttrInfo(attrInfo);

    // Reconfigure Vertex Buffer Info
    C3D_BufInfo* bufInfo = C3D_GetBufInfo();
    BufInfo_Init(bufInfo);
    BufInfo_Add(bufInfo, vbo_data, sizeof(vertex), 3, 0x210);
	C3D_SetBufInfo(bufInfo);

    // Draw the VBO
	C3D_DrawArrays(GPU_TRIANGLES, 0, vertices.size());
};

template<typename type>
inline type mesh::GetVertices(bool data) const {
    if(data)
	    return vertices.data();
	else
	    return vertices.size();
};

template<typename type>
inline type mesh::GetIndices(bool data) const {
    if(data)
	    return indices.data();
	else
	    return indices.size();
};

// Destroy the 3D model
mesh::~mesh() {
    // Free the texture
	C3D_TexDelete(&tex);

	// Clear vectors
    vertices.clear();
    indices.clear();
	
	// Free the Buffer Objects
	linearFree(vbo_data);
    linearFree(ibo_data);
}