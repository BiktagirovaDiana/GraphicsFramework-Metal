//
//  Texture.hpp
//  MetalApp 2
//
//  Created by Macbook on 16.10.2026.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <cstdint>
#include <sstream>
#include <iostream>

#include "Metal/Metal.hpp"


class Texture
{
public:
    Texture(std::string nameImage, MTL::Device* device);
    ~Texture();
    void LoadTexture(std::string nameImage, MTL::Device* device);
    void CreateSampler(MTL::Device* device);
    
    MTL::Texture* GetTexture();
    MTL::SamplerState* GetSampler();
private:
    int width;
    int height;
    int channels;
    
    std::vector<uint8_t> pixels;
    
    MTL::Texture* texture = nullptr;
    MTL::SamplerState* state = nullptr;
};

#endif /* Texture_hpp */
