 //
//  DepthBuffe.hpp
//  MetalApp 2
//
//  Created by Macbook on 04.10.2026.
//

#ifndef DepthBuffer_hpp
#define DepthBuffer_hpp

#include "Metal/Metal.hpp"

class DepthBuffer
{
public:
    DepthBuffer();
    ~DepthBuffer();
    void CreateDepthTexture(MTL::Device *device, NS::UInteger width, NS::UInteger height);
    MTL::Texture *GetDepthTexture();

private:
    MTL::Texture* depthTexture = nullptr;
    MTL::DepthStencilState* depthState = nullptr;
    
};

#endif /* DepthBuffer_hpp */
