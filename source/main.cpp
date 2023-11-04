// Created by Lollio64, 31/10/23

// Standard include files
#include <iostream>

// devkitPro include files
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

// Insert custom header files here
#include <gfx/gfx.h>
#include <gfx/model.h>

// Define some stuff
#define CLEAR_COLOR 0x68B0D8FF
#define DISPLAY_TRANSFER_FLAGS (GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

// MAIN FUNCTION
int main() {
    // Init romfs
    romfsInit();

    // Init graphics
    gfxInitDefault();
    consoleInit(GFX_BOTTOM, NULL); // Debug console output
    std::cout << "Initializing graphics..." << "\n";
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); // 3D Graphics
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS); // 2D Graphics
    std::cout << "Initialized graphics successfully!" << "\n";
 
    std::cout << "Initialize render target..." << "\n"; 
    // Initialize a render target for the top screen to tell Citro3D to which screen to render to 
    C3D_RenderTarget* leftTarget = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
    C3D_RenderTargetSetOutput(leftTarget, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
    std::cout << "Initialized render target successfully!" << "\n";

    // Instantiate some objects. move to scenes
    std::cout << "Instantiate class objects..." << "\n";
    gfx::GFX gfx;
    model testMDL("romfs:/models/test.mdlf");
    std::cout << "Instantiated objects successfully!" << "\n";

    // Main Loop
    while(aptMainLoop()) {
        // Scan user input every frame
        hidScanInput();
        
        // Check if a key has been pressed
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) {
            break; // Break in order to return to the Homebrew Launcher, Debug only
        }

        // Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C3D_RenderTargetClear(leftTarget, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
		C3D_FrameDrawOn(leftTarget);
		testMDL.render();
		C3D_FrameEnd(0);
    };

    // Print stuff
    std::cout << "Deinitializing graphics..." << "\n";
     
    // Deinit romfs
    romfsExit();

    // Deinit graphics
    C2D_Fini();
    C3D_Fini();
    std::cout << "Deinitialized graphics successfully!" << "\n";
    gfxExit();
    return 0;
};
