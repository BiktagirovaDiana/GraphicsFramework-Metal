//
//  Renderer.cpp
//  MetalApp
//
//  Created by Macbook on 24.03.2026.
//
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "Renderer.hpp"
#include <iostream>


namespace
{
}

Renderer::Renderer(MTL::Device* device)
{
    CreateRenderPipeline(device);
    CreateDepth(device);
    
}


void Renderer::Draw(CA::MetalDrawable* drawable, MTL::Device* device)
{
    MTL::Texture* drawableTexture = drawable->texture();
    depthBuffer.CreateDepthTexture(device, drawableTexture->width(), drawableTexture->height());
    CreateRenderRenderPassDescriptor();

    MTL::CommandQueue* commandQueue = device->newCommandQueue(); //очередь буффер команд из GPU
    MTL::CommandBuffer* cmdBuf = commandQueue->commandBuffer(); //буфер команд
    
    
    ClearColor(renderPassDescriptor, cmdBuf, drawable);
    //DrawTriangle(renderPassDescriptor, cmdBuf, drawable, device);
    DrawCube(renderPassDescriptor, cmdBuf, drawable, device);
    
    cmdBuf->presentDrawable(drawable); //вывод на экран
    cmdBuf->commit(); //отправка буффера команд в очередь из буфферов команд (CommandQueue)
    
    //vertexBuffer->release();
    commandQueue->release(); //освобождаем очередь команд
    renderPassDescriptor->release(); //свобода
}
void Renderer::ClearColor(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf, CA::MetalDrawable* drawable)
{
    //указываем где мы рисуем (текстура для рисования), в нашем случае на экране drawable
    renderPassDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    //очистка экрана
    renderPassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    //заполнение цветом
    renderPassDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.55, 0.55, 0.55, 1.0));
    
    MTL::RenderCommandEncoder* encoder = cmdBuf->renderCommandEncoder(renderPassDescriptor);
    encoder->endEncoding(); //окончание рендер прохода
}

void Renderer::DrawTriangle(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable, MTL::Device* device)
{
    MTL::Buffer* vertexBuffer = geometry.CreateTriangleBuffer(device); //создаем буффер с данными вершин треугольника
    MTL::RenderCommandEncoder* encoder = cmdBuf->renderCommandEncoder(renderPassDescriptor);
    encoder->setRenderPipelineState(pipelineState);
    encoder->setVertexBuffer(vertexBuffer, 0 ,0);
    encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0),NS::UInteger(3));
    encoder->endEncoding();
}
void Renderer::DrawSquare(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable, MTL::Device* device)
{
    MTL::Buffer* vertexBuffer = geometry.CreateSquareBuffer(device);
    MTL::RenderCommandEncoder* encoder = cmdBuf->renderCommandEncoder(renderPassDescriptor);
    encoder->setRenderPipelineState(pipelineState);
    encoder->setVertexBuffer(vertexBuffer, 0 ,0);
    simd::float4 red = {1.0f, 0.0f, 0.0f, 1.0f};
    encoder->setFragmentBytes(&red, sizeof(red), 0);
    encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, NS::UInteger(0),NS::UInteger(6));
    encoder->endEncoding();
}

void Renderer::DrawCube(MTL::RenderPassDescriptor* renderPassDescriptor, MTL::CommandBuffer* cmdBuf,CA::MetalDrawable* drawable,
                        MTL::Device* device)
{
    MTL::Buffer* vertexBuffer = geometry.CreateCubeBuffer(device);
    MTL::Buffer* indexBuffer = device-> newBuffer(geometry.indices, sizeof(geometry.indices), MTL::ResourceStorageModeShared);
    MTL::RenderCommandEncoder* encoder = cmdBuf->renderCommandEncoder(renderPassDescriptor);
    encoder->setRenderPipelineState(pipelineState);
    encoder -> setVertexBuffer(vertexBuffer, 0 ,0);
    matrix_float4x4 modelMatrix = matrix.MakeRotation(45.0f, 45.0f, 45.0f);
    encoder -> setVertexBytes(&modelMatrix, sizeof(modelMatrix), 1);
    simd::float4 red = {1.0f, 0.0f, 0.0f, 1.0f};
    encoder->setFragmentBytes(&red, sizeof(red), 0);
    encoder->setDepthStencilState(depthStencilState);
    encoder -> drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, 36, MTL::IndexTypeUInt16, indexBuffer, 0);
    encoder->setRenderPipelineState(pipelineState);
    encoder->endEncoding();
}

void Renderer::CreateDepth(MTL::Device* device)
{
    depthStencilDescriptor = MTL::DepthStencilDescriptor::alloc()->init();
    depthStencilDescriptor->setDepthCompareFunction(MTL::CompareFunctionLess);
    depthStencilDescriptor->setDepthWriteEnabled(true);
    depthStencilState = device->newDepthStencilState(depthStencilDescriptor);
}
void Renderer::CreateRenderRenderPassDescriptor()
{
    renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init(); //заполняем буффер команд
    renderPassDescriptor->depthAttachment()->setTexture(depthBuffer.GetDepthTexture());
    renderPassDescriptor->depthAttachment()->setLoadAction(MTL::LoadActionClear); //очистка буффера глубины перед отрисовкой
    renderPassDescriptor->depthAttachment()->setClearDepth(1.0);
}

void Renderer::CreateRenderPipeline(MTL::Device* device)
{
    MTL::Library* library = device->newDefaultLibrary(); //берем скомпилированную библиотеку шейдеров метал
    MTL::Function* vertexFunction = library->newFunction(NS::String::string("vertexShader", NS::UTF8StringEncoding));
    MTL::Function* fragmentFunction = library->newFunction(NS::String::string("fragmentShader", NS::UTF8StringEncoding));
    
    //штука для настроек рендера паплайна (просто указывает вертекс/фрагмент шейдер и способ вывода)
    MTL::RenderPipelineDescriptor* pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();

    pipelineDescriptor-> setVertexFunction(vertexFunction);
    pipelineDescriptor-> setFragmentFunction(fragmentFunction);
    
    
    pipelineDescriptor->colorAttachments() ->object(0) ->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    pipelineDescriptor->setDepthAttachmentPixelFormat(MTL::PixelFormatDepth32Float);
    
    NS::Error* error = nullptr;
    pipelineState = device -> newRenderPipelineState(pipelineDescriptor, &error);
}
