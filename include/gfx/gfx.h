// Created by Lollio64 1/11/23

// Include guards
#ifndef WIND_WAKER_3D_GFX_H
#define WIND_WAKER_3D_GFX_H

// Default includes
#include <iostream>

// devkitPro include
#include <citro3d.h>

// Custom includes
#include <engine/vector.h>

namespace gfx {
    class GFX {
        public:
        GFX();
        ~GFX();

        // Vertex Shader
        DVLB_s* vshader_dvlb;
        shaderProgram_s program;
        int uLoc_projection, uLoc_modelView;
        
        // Matrices
        C3D_Mtx modelView;
        C3D_Mtx projection;

        // Lighting
        C3D_LightEnv lightEnv;
        C3D_Light light;
        C3D_LightLut lut_Spec; 
        C3D_LightLut lut_Toon;

        static void* vbo_data;
        static void* ibo_data;
    }
}

#endif