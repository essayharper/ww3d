// Created by Lollio64, 31/10/23

// Standard include files
#include <iostream>

// devkitPro include files
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

// Insert custom header files here

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
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); // 3D Graphics
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS); // 2D Graphics

    // Initialize a render target for the top screen to tell Citro3D to which screen to render to 
    C3D_RenderTarget* leftTarget = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
    C3D_RenderTargetSetOutput(leftTarget, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

    // Print stuff
    std::cout << "Initializing Scene..." << "\n";

    // Main Loop
    while(aptMainLoop()) {
        // Allow fo user input
        hidScanInput();
        
        // Respond to user input
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) {
            break; // Break in order to return to the Homebrew Launcher, Debug only
        }
    };

    // Print stuff
    std::cout << "Deinitializing Scene..." << "\n";
     
    // Deinit romfs
    romfsExit();

    // Deinit graphics
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
};
