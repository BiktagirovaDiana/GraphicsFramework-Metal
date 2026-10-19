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

Renderer::Renderer(MTL::Device* device, Controller* controller) :  device(device), controller(controller), locationTexture("Location.png", device)
{
    commandQueue = device->newCommandQueue(); //очередь буффер команд из GPU
    CreateRenderPipeline();
    CreateDepth();

    //CreateModel("Cube", cube);
    CreateModel("Location", location);
}
Renderer::~Renderer()
{
    commandQueue->release(); //освобождаем очередь команд
    pipelineState->release();
    depthStencilState->release();
}

void Renderer::CreateModel(std::string NameModel, Geometry& model)
{
    parser.OpenModel(NameModel);
    
    model.SetModelVertex(device, parser.GetModelVertex());
    model.SetModelIndexVertex(device, parser.GetModelIndexVertex());
    model.SetModelNormal(device, parser.GetModelNormal());
    model.SetModelIndexNormal(device, parser.GetModelIndexNormal());
    model.SetModelUV(device, parser.GetModelUV());
    model.SetModelIndexUV(device, parser.GetModelIndexUV());
    
};

void Renderer::UpdateMatrices(CA::MetalDrawable* drawable)
{
    MTL::Texture* drawableTexture = drawable->texture();
    viewMatrix = matrix.ViewMatrix(cameraPosition, cameraTarget, cameraUp);
    projectionMatrix = matrix.ProjectionMatrix(
        static_cast<int>(drawableTexture->width()),
        static_cast<int>(drawableTexture->height()),
        60,
        0.001f,
        50.0f);
}

void Renderer::UpdateDeltaTime()
{
    auto currentTime = std::chrono::steady_clock::now();

    deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
    lastFrameTime = currentTime;
}
void Renderer::Draw(CA::MetalDrawable* drawable)
{
    if (drawable == nullptr)
    {
        return;
    }
        
    MTL::Texture* drawableTexture = drawable->texture();
    MTL::Texture* depthTexture = depthBuffer.GetDepthTexture();
    if(depthTexture == nullptr || depthTexture->width() != drawableTexture->width() ||depthTexture->height() != drawableTexture->height())
    {
        depthBuffer.CreateDepthTexture(device, drawableTexture->width(), drawableTexture->height());
    }
    
    CreateRenderRenderPassDescriptor(drawable);
    MTL::CommandBuffer* cmdBuf = commandQueue->commandBuffer(); //буфер команд
    MTL::RenderCommandEncoder* encoder = cmdBuf->renderCommandEncoder(renderPassDescriptor);
    encoder->setRenderPipelineState(pipelineState);
    encoder->setDepthStencilState(depthStencilState);
    UpdateDeltaTime();
    
    UpdateCamera(deltaTime);
    UpdateMatrices(drawable);
    DrawModel(encoder, location);
    
    
    encoder->endEncoding();
    cmdBuf->presentDrawable(drawable); //вывод на экран
    cmdBuf->commit(); //отправка буффера команд в очередь из буфферов команд (CommandQueue)
    
    renderPassDescriptor->release(); //свобода
    
    
}
void Renderer::UpdateCamera(float deltaTime)
{
    if (!controller)
    {
        return;
    }

        float cameraSpeed = 3.0f * deltaTime;

        simd::float3 forward = simd::normalize(cameraTarget - cameraPosition);

        simd::float3 right = simd::normalize(simd::cross(forward, cameraUp));

        simd::float3 movement = {0.0f, 0.0f, 0.0f};

    if (controller->IsKeyDown(Key::W))
    {
        movement += forward;
    }
            

    if (controller->IsKeyDown(Key::S))
    {
        movement -= forward;
    }
            

    if (controller->IsKeyDown(Key::A))
    {
        movement -= right;
    }
           

    if (controller->IsKeyDown(Key::D))
    {
        movement += right;
    }
            

    if (controller->IsKeyDown(Key::Space))
    {
        movement += cameraUp;
    }
           

    if (controller->IsKeyDown(Key::Shift))
    {
        movement -= cameraUp;
    }
            
    cameraPosition += movement * cameraSpeed;
    cameraTarget += movement * cameraSpeed;
}

void Renderer::DrawModel(MTL::RenderCommandEncoder* encoder, Geometry& model)
{
    modelMatrix = matrix.MakeRotation(0.0f, 0.0f, 0.0f);
    encoder -> setVertexBytes(&modelMatrix, sizeof(modelMatrix), 1);
    encoder -> setVertexBytes(&viewMatrix, sizeof(viewMatrix), 2);
    encoder -> setVertexBytes(&projectionMatrix, sizeof(projectionMatrix), 3);
    encoder -> setVertexBuffer(model.GetModelBufferVertex(), 0 ,0);
    encoder -> setVertexBuffer(model.GetModelBufferNormal(), 0, 4);
    encoder -> setVertexBuffer(model.GetModelBufferIndexVertex(), 0, 5);
    encoder -> setVertexBuffer(model.GetModelBufferIndexNormal(), 0, 6);
    encoder -> setVertexBuffer(model.GetModelBufferUV(), 0, 7);
    encoder -> setVertexBuffer(model.GetModelBufferIndexUV(), 0, 8);
    
    if(n < 181)
    {
        n = n + 1;
    }
    else{
        n = 0;
    }
   

    encoder->setFragmentTexture(locationTexture.GetTexture(), 0);
    encoder->setFragmentSamplerState(locationTexture.GetSampler(), 0);

    encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, static_cast<NS::UInteger>(0),static_cast<NS::UInteger>(model.GetModelIndexVertex().size()));

}

void Renderer::CreateDepth()
{
    depthStencilDescriptor = MTL::DepthStencilDescriptor::alloc()->init();
    depthStencilDescriptor->setDepthCompareFunction(MTL::CompareFunctionLess);
    depthStencilDescriptor->setDepthWriteEnabled(true);
    depthStencilState = device->newDepthStencilState(depthStencilDescriptor);
    
    depthStencilDescriptor->release();
}
void Renderer::CreateRenderRenderPassDescriptor(CA::MetalDrawable* drawable)
{
    renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
    //указываем где мы рисуем (текстура для рисования), в нашем случае на экране drawable
    renderPassDescriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    //очистка экрана
    renderPassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    //заполнение цветом
    renderPassDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.55, 0.55, 0.55, 1.0));
    renderPassDescriptor->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);
    
    
    renderPassDescriptor->depthAttachment()->setTexture(depthBuffer.GetDepthTexture());
    renderPassDescriptor->depthAttachment()->setLoadAction(MTL::LoadActionClear); //очистка буффера глубины перед отрисовкой
    renderPassDescriptor->depthAttachment()->setClearDepth(1.0);
    renderPassDescriptor->depthAttachment()->setStoreAction(MTL::StoreActionDontCare);
}

void Renderer::CreateRenderPipeline()
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
    
    vertexFunction->release();
    fragmentFunction->release();
    pipelineDescriptor->release();
    library->release();
}

