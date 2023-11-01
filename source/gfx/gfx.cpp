// Created by Lollio64 1/11/23
#include <iostream>
#include <gfx/gfx.h>
#include "vshader_shbin.h"

gfx::GFX::GFX() {
    // Load the vertex shader, create a shader program and bind it
    vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
    shaderProgramInit(&shader);
    shaderProgramSetVsh(&shader, &vshader_dvlb->DVLE[0]);
    C3D_BindProgram(&shader);

    // Get the location of the uniforms
    uLoc_projection   = shaderInstanceGetUniformLocation(shader.vertexShader, "projection");
    uLoc_modelView    = shaderInstanceGetUniformLocation(shader.vertexShader, "modelView");

    // Compute the projection matrix
    Mtx_PerspTilt(&projection_matrix, C3D_AngleFromDegrees(60.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, left_hand);
}