#ifndef WW3D_GFX_H
#define WW3D_GFX_H

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include "vertex_shbin.h"

class gfx {
    public:
    // Init/Exit Graphics
    static void InitGfx();
    static void ExitGfx();

    // Vertex Shader
    static DVLB_s* vertex_dvlb;
    static shaderProgram_s program;
    static int uLoc_projection, uLoc_modelView;

    // Projection Matrices
    static C3D_Mtx projTop;
    static C3D_Mtx projBot;

    // Top and Bottom Render Target
    static C3D_RenderTarget* top;
    static C3D_RenderTarget* bottom;

    // Clear Color: Light Blue/Black
    static constexpr u32 CLEAR_COLOR = 0x68B0D8FF;

    // Display Transfer Flags
    static constexpr u32 DISPLAY_TRANSFER_FLAGS = \
	    (GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	    GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	    GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO));

    // Sprite Sheet
    static C2D_SpriteSheet spriteSheet;
};
#endif //WW3D_GFX_H