//
//  Renderer.hpp
//  MetalApp
//
//  Created by Macbook on 24.03.2026.
//

#ifndef Renderer_hpp
#include "Metal/Metal.hpp"
#include "Geometry.hpp"
#include "Matrix.hpp"
#include "QuartzCore/CAMetalDrawable.hpp"
#include "DepthBuffer.hpp"
#include "Controller.hpp"
#include "Parser.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include <chrono>
#include <simd/simd.h>
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION


class Renderer
{
public:
    Renderer(MTL::Device* device, Controller* controller);
    ~Renderer();
    
    void CreateModel(std::string NameModel, Geometry& model, Material& material);
    
    void Draw(CA::MetalDrawable* drawable);
    void DrawModel(MTL::RenderCommandEncoder* encoder, Geometry& model, matrix_float4x4& modelMatrix);
    
    void CreateRenderPipeline();
    void CreateRenderRenderPassDescriptor(CA::MetalDrawable* drawable);
    void CreateDepth();
    
    void UpdateCamera(float deltaTime);
    void UpdateMatrices(CA::MetalDrawable* drawable);
    void UpdateDeltaTime();
    
    
    
    
private:
    MTL::RenderPipelineState* pipelineState = nullptr;
    MTL::RenderPassDescriptor* renderPassDescriptor = nullptr;
    MTL::DepthStencilState* depthStencilState = nullptr;
    MTL::DepthStencilDescriptor* depthStencilDescriptor = nullptr;
    
    Controller* controller = nullptr;
    MTL::Device* device = nullptr;
    MTL::CommandQueue* commandQueue = nullptr; //очередь буффер команд из GPU
    
    simd_float3 cameraTarget = {0.0f, 0.0f, 0.0f};
    simd_float3 cameraUp = {0.0f, 1.0f, 0.0f};
    simd_float3 cameraPosition = {0.0f, 0.0f, 5.0f};
    float n = 0;
    
    //matrix_float4x4 modelMatrix = matrix_identity_float4x4;
    matrix_float4x4 viewMatrix = matrix_identity_float4x4;
    matrix_float4x4 projectionMatrix = matrix_identity_float4x4;
    
    std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
    float deltaTime = 0.0f;
    
    Geometry location;
    Material locationMaterial;
    
    Geometry anchor;
    Material anchorMaterial;
    
    Matrix matrix;
    DepthBuffer depthBuffer;
    Parser parser;
    
    
};

#define Renderer_hpp

#include <stdio.h>

#endif /* Renderer_hpp */
