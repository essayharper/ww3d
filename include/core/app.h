#ifndef WW3D_APP_H
#define WW3D_APP_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include "gfx.h"
#include "scene.h"

class app {
    public:
    // Init/Exit App
    app(); ~app();
    
    // Main Loop
    void RunApp();

    // Touch/Circle Pad Position
    touchPosition tpos;
    circlePosition pos, cpos;

    // Gyro Angle and Input Scanning
    u32 kDown, kUp, kHeld; 
    angularRate rate;
 
    // Current Scene
    SceneType type;

    // Instance
    u8 counter;
};
#endif //WW3D_APP_H