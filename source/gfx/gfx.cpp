// Created by Lollio64 1/11/23
#include <iostream>
#include <cmath>
#include <gfx/gfx.h>
#include <vshader_shbin.h>
#include <citro3d.h>

gfx::GFX::GFX() {
    // Load the vertex shader, create a shader program and bind it
    vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
    shaderProgramInit(&program);
    shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
    C3D_BindProgram(&program);

    // Get the location of the uniforms
    uLoc_projection = shaderInstanceGetUniformLocation(program.vertexShader, "projection");
    uLoc_modelView  = shaderInstanceGetUniformLocation(program.vertexShader, "modelView");

    // Compute the projection matrix
    Mtx_PerspTilt(&projection, C3D_AngleFromDegrees(80.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, leftHand);

    // Material
    static const C3D_Material material = {
        { 0.4f, 0.4f, 0.4f }, //ambient
        { 0.4f, 0.4f, 0.4f }, //diffuse
        { 0.2f, 0.2f, 0.2f }, //specular0
        { 0.0f, 0.0f, 0.0f }, //specular1
        { 0.0f, 0.0f, 0.0f }, //emission
    };

    // Setup lighting enviroment
    C3D_LightEnvInit(&lightEnv);
    C3D_LightEnvBind(&lightEnv);
    C3D_LightEnvMaterial(&lightEnv, &material);

    LightLut_Phong(&lut_Phong, 30);
    C3D_LightEnvLut(&lightEnv, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &lut_Phong);
}

gfx::GFX::~GFX() {
    // Free the shader program
    shaderProgramFree(&program);
    DVLB_Free(vshader_dvlb);
}
