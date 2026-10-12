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
#include <simd/simd.h>
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION


class Renderer
{
public:
    Renderer(MTL::Device* device);
    Renderer(MTL::Device* device, Controller* controller);
    void Draw(CA::MetalDrawable* drawable, MTL::Device* device);
    void ClearColor(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable);
    void DrawTriangle(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable, MTL::Device* device);
    void DrawSquare(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable,
        MTL::Device* device);
    void DrawCube(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable,
        MTL::Device* device);
    void DrawModel(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable,
                   MTL::Device* device, std::string nameModel);
    matrix_float4x4 modelMatrix = matrix_identity_float4x4;
    matrix_float4x4 viewMatrix = matrix_identity_float4x4;
    matrix_float4x4 projectionMatrix = matrix_identity_float4x4;
    Geometry geometry;
    Matrix matrix;
    DepthBuffer depthBuffer;
    Parser parser;
private:
    MTL::RenderPipelineState* pipelineState = nullptr;
    MTL::RenderPassDescriptor* renderPassDescriptor = nullptr;
    Controller* controller = nullptr;
    simd_float3 cameraPosition = {0.0f, 0.0f, 5.0f};
    void CreateRenderPipeline(MTL::Device* device);
    void CreateRenderRenderPassDescriptor();
    void CreateDepth(MTL::Device* device);
    MTL::DepthStencilDescriptor* depthStencilDescriptor = nullptr;
    MTL::DepthStencilState* depthStencilState = nullptr;
    
};

#define Renderer_hpp

#include <stdio.h>

#endif /* Renderer_hpp */
