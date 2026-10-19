//
//  Texture.cpp
//  MetalApp 2
//
//  Created by Macbook on 16.10.2026.
//
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"


Texture::Texture(std::string nameImage, MTL::Device* device)
{
    LoadTexture(nameImage, device);
    CreateSampler(device);
    
}
Texture::~Texture()
{
    if (texture)
    {
        texture->release();
    }
    if (state)
    {
        state->release();
    }
}

void Texture::LoadTexture(std::string nameImage, MTL::Device* device)
{
    if(!(texture == nullptr))
    {
        texture->release();
        texture = nullptr;
    }
    std::string fileName = "Assets/Models/" + nameImage;
    
    unsigned char* data = stbi_load(fileName.c_str(),&width, &height, &channels, STBI_rgb_alpha);
    size_t size = static_cast<size_t>(width) * height * 4;
    
    if (!data)
    {
        std::cout << "Ошибка загрузки текстуры: " << stbi_failure_reason() << std::endl;
        return;
    }

    pixels.assign(data, data + size);
    stbi_image_free(data);
    
    MTL::TextureDescriptor* descriptor = MTL::TextureDescriptor::alloc()->init();
    descriptor->setTextureType(MTL::TextureType2D);
    descriptor->setWidth(width);
    descriptor->setHeight(height);
    descriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    descriptor->setUsage(MTL::TextureUsageShaderRead);
    
    MTL::Region region = MTL::Region::Make2D(0, 0, width, height);
    texture = device->newTexture(descriptor);
    
    texture->replaceRegion(region, 0, pixels.data(), width * 4);
    descriptor->release();
    pixels.clear();
    pixels.shrink_to_fit();
    
}

void Texture::CreateSampler(MTL::Device* device)
{
    if(!(state == nullptr))
    {
        state->release();
    }
    MTL::SamplerDescriptor* descriptor = MTL::SamplerDescriptor::alloc()->init();
    descriptor->setMinFilter(MTL::SamplerMinMagFilterLinear);
    descriptor->setMagFilter(MTL::SamplerMinMagFilterLinear);
    descriptor->setMipFilter(MTL::SamplerMipFilterNotMipmapped);
    
    descriptor->setSAddressMode(MTL::SamplerAddressModeRepeat);
    descriptor->setTAddressMode(MTL::SamplerAddressModeRepeat);
    
    state = device->newSamplerState(descriptor);
    descriptor->release();
}

MTL::Texture *Texture::GetTexture()
{
    return texture;
}
MTL::SamplerState *Texture::GetSampler()
{
    return state;
}
