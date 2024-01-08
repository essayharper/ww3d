#include "app.h"

app::app() {
    // Increment Instance Count
    counter++;

    if(counter > 1)
        // Init Gfx
        gfxInitDefault();
        gfx::InitGfx();

        // Init romfs
        romfsInit();
};

void app::RunApp() {
    while(aptMainLoop()) {
        // Poll Input
        kUp   = hidKeysUp();
        kDown = hidKeysDown();
        kHeld = hidKeysHeld();

        // Read Touch Position
        hidTouchRead(&tpos);

        // Read Circle Pad Position
        hidCircleRead(&pos);
        hidCstickRead(&cpos);

        // Break in order to return to the Homebrew Launcher
        if(kDown & KEY_START) break;

        // Render Frame
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            C3D_RenderTargetClear(gfx::top, C3D_CLEAR_ALL, gfx::CLEAR_COLOR, 0);
            C3D_FrameDrawOn(gfx::top);
            C2D_SceneTarget(gfx::top);
            sceneDrawTop(type);
                C3D_RenderTargetClear(gfx::bottom, C3D_CLEAR_ALL, gfx::CLEAR_COLOR, 0);
                C3D_FrameDrawOn(gfx::bottom);
                C2D_SceneTarget(gfx::bottom);
                sceneDrawBot(type);
        C3D_FrameEnd(0);
    };
};

app::~app() {
    if(counter > 1)
        // Exit romfs
        romfsExit();

        // Exit Gfx
        gfx::ExitGfx();
        gfxExit();

    // Decrement Instance Count
    counter--;
};