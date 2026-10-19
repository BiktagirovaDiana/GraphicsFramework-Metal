//
//  DepthBuffer.cpp
//  MetalApp 2
//
//  Created by Macbook on 04.10.2026.
//

#include "DepthBuffer.hpp"

DepthBuffer::DepthBuffer()
{
    
}

DepthBuffer::~DepthBuffer()
{
    if(depthTexture)
    {
        depthTexture->release();
    }
    
}
void DepthBuffer::CreateDepthTexture(MTL::Device *device, NS::UInteger width, NS::UInteger height)
{
    
    MTL::TextureDescriptor* depgthDescriptor = MTL::TextureDescriptor::texture2DDescriptor(MTL::PixelFormatDepth32Float,  width,  height, false);
    depgthDescriptor->setUsage(MTL::TextureUsageRenderTarget);
    depgthDescriptor->setStorageMode(MTL::StorageModePrivate);
    
    depgthDescriptor->setUsage(MTL::TextureUsageRenderTarget);
    depgthDescriptor->setStorageMode(MTL::StorageModePrivate);
    
    if (depthTexture)
    {
        depthTexture->release();
        depthTexture = nullptr;
    }
    depthTexture = device->newTexture(depgthDescriptor);
}

MTL::Texture *DepthBuffer::GetDepthTexture()
{
    return depthTexture;
}
