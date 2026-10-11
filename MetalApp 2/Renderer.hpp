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
#include <simd/simd.h>
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION


class Renderer
{
public:
    Renderer(MTL::Device* device);
    void Draw(CA::MetalDrawable* drawable, MTL::Device* device);
    void ClearColor(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable);
    void DrawTriangle(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable, MTL::Device* device);
    void DrawSquare(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable,
        MTL::Device* device);
    void DrawCube(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable,
        MTL::Device* device);
    matrix_float4x4 modelMatrix = matrix_identity_float4x4;
    Geometry geometry;
    Matrix matrix;
    DepthBuffer depthBuffer;
    
private:
    MTL::RenderPipelineState* pipelineState = nullptr;
    MTL::RenderPassDescriptor* renderPassDescriptor = nullptr;
    void CreateRenderPipeline(MTL::Device* device);
    void CreateRenderRenderPassDescriptor();
    void CreateDepth(MTL::Device* device);
    MTL::DepthStencilDescriptor* depthStencilDescriptor = nullptr;
    MTL::DepthStencilState* depthStencilState = nullptr;
    
   
    
};




#define Renderer_hpp

#include <stdio.h>

#endif /* Renderer_hpp */
