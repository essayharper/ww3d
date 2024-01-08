#ifndef WW3D_SCENE_H
#define WW3D_SCENE_H

#include "gfx.h"
#include "actor.h"
#include <vector>

typedef enum {
    SCENE_DEFAULT,
    SCENE_OUTSET_ISLAND,
} SceneType;

class scene {
    public:
    virtual ~scene() = default;

    private:
    std::vector<actor> Actorlist;
};

// Draw and Calc the Scene
void sceneDrawTop(SceneType type) {
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, gfx::uLoc_projection, &gfx::projTop);
};

void sceneDrawBot(SceneType type) {
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, gfx::uLoc_projection, &gfx::projBot);
};
#endif //WW3D_SCENE_H