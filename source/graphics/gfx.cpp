#include "gfx.h"

// Vertex Shader
DVLB_s* gfx::vertex_dvlb = NULL;
shaderProgram_s gfx::program;
int gfx::uLoc_projection, gfx::uLoc_modelView;

// Projection Matrices
C3D_Mtx gfx::projTop;
C3D_Mtx gfx::projBot;

// Top and Bottom Render Target
C3D_RenderTarget* gfx::top = NULL;
C3D_RenderTarget* gfx::bottom = NULL;

// Sprite Sheet
C2D_SpriteSheet gfx::spriteSheet;

// Initialize the gfx of a scene
void gfx::InitGfx() {
	// Init citro3d/2d
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

	// Initialize the render targets
	top = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(top, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

	bottom = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(bottom, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

    // Load the vertex shader, create a shader program and bind it
	vertex_dvlb = DVLB_ParseFile((u32*)vertex_shbin, vertex_shbin_size);
	shaderProgramInit(&program);
	shaderProgramSetVsh(&program, &vertex_dvlb->DVLE[0]);
	C3D_BindProgram(&program);

	// Get the location of the uniforms
	uLoc_projection   = shaderInstanceGetUniformLocation(program.vertexShader, "projection");
	uLoc_modelView    = shaderInstanceGetUniformLocation(program.vertexShader, "modelView");

	// Load graphics
	//spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	//if(!spriteSheet) svcBreak(USERBREAK_PANIC);

	// Compute the projection matrices
	Mtx_PerspTilt(&projTop, C3D_AngleFromDegrees(80.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, false);
    Mtx_OrthoTilt(&projBot, -160.0f, 160.0f, 0.0f, 240.0f, 0.0f, 1.0f, true);
};

// Deinitialize the gfx of a scene
void gfx::ExitGfx() {
	// Delete the Render Targets
    C3D_RenderTargetDelete(top);
	C3D_RenderTargetDelete(bottom);

	// Delete graphics
	C2D_SpriteSheetFree(spriteSheet);
	
	// Free the Vertex Shader 
	shaderProgramFree(&program);
	DVLB_Free(vertex_dvlb);

	// Deinit citro2d/3d
	C2D_Fini();
	C3D_Fini();
};