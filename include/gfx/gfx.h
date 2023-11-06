// Created by Lollio64 1/11/23

// Include guards
#ifndef WIND_WAKER_3D_GFX_H
#define WIND_WAKER_3D_GFX_H

// Default includes
#include <iostream>

// devkitPro includes
#include <citro3d.h>
#include <vshader_shbin.h>

// Custom includes
#include <engine/vertex.h>

namespace gfx {
    class GFX {
        public:
        GFX();
        ~GFX();

        // Vertex Shader
        DVLB_s* vshader_dvlb;
        shaderProgram_s program;
        int uLoc_projection, uLoc_modelView;

        // Camera struct
        struct cam {
            C3D_FVec camPos;
            C3D_FVec camTarget;
            C3D_FVec lightPos;
        };
        
        // Texture
        C3D_Tex* texture;

        // Matrices
        C3D_Mtx modelView;
        C3D_Mtx projection;

        // Lighting
        C3D_LightEnv lightEnv;
        C3D_Light light;
        C3D_LightLut lut_Phong;
        C3D_LightLut lut_Spec; 
        C3D_LightLut lut_Toon;
 
        // Buffer Objects
        static void* vbo_data;
        static void* ibo_data;
    };
};
#endif
