#ifndef WW3D_MESH_H
#define WW3D_MESH_H

#include "vector.h"
#include "player.h"
#include "gfx.h"
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>

class mesh {
    public:
    mesh(std::string path); ~mesh();

    // Draw the Mesh
    void Draw(player &ply);
    vec3 position, rotation, scale;

    // Get access to mesh data
    template<typename type>
    inline type GetVertices(bool data) const;

    template<typename type>
    inline type GetIndices(bool data) const;

    private:
    // Vertices | vector for collision | vertex pointer for VBO
    using vertex = struct {vec3 position; vec2 uv; vec3 normal;};
    std::vector<vertex> vertices; vertex* vbo_data;

    // Indices | vector for collision | index pointer for IBO
    using index = unsigned short;
    std::vector<index> indices; index* ibo_data;

    // Texture & Model Matrix
    C3D_Tex tex; C3D_Mtx modelMtx;
};
#endif //WW3D_MESH_H