//
//  Geometry.hpp
//  MetalApp 2
//
//  Created by Macbook on 03.10.2026.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include "Metal/Metal.hpp"
#include "Texture.hpp"
#include <simd/simd.h>
#include <vector>

struct Vertex
{
    simd::float3 position;
    simd::float4 color;
};

class Geometry
{
public:
    Geometry(MTL::Device* device);
    ~Geometry();
    
    MTL::Buffer* CreateTriangleBuffer();
    MTL::Buffer* CreateSquareBuffer();
    MTL::Buffer* CreateCubeBuffer();
    MTL::Buffer* CreatePlaneBuffer();
    
    
    void SetModelVertex(std::vector <float> Vertex);
    void SetModelNormal(std::vector <float> Normal);
    void SetModelUV(std::vector <float> UV);
    void SetModelIndexVertex(std::vector <uint16_t> Index);
    void SetModelIndexNormal(std::vector <uint16_t> Index);
    void SetModelIndexUV(std::vector <uint16_t> Index);

    
    
    std::vector<float> GetModelVertex();
    std::vector<float> GetModelNormal();
    std::vector<float> GetModelUV();
    std::vector<uint16_t> GetModelIndexVertex();
    std::vector<uint16_t> GetModelIndexNormal();
    std::vector<uint16_t> GetModelIndexUV();
    
    MTL::Buffer* GetModelBufferVertex();
    MTL::Buffer* GetModelBufferNormal();
    MTL::Buffer* GetModelBufferUV();
    MTL::Buffer* GetModelBufferIndexVertex();
    MTL::Buffer* GetModelBufferIndexNormal();
    MTL::Buffer* GetModelBufferIndexUV();
    
    void CreateNormal();
    void ClearAll();
    
    void SetTexture(std::string nameTextureModel);
    Texture* GetTexture();
    
private:
    MTL::Device* device = nullptr;
    
    std::vector <float> modelVertex;
    std::vector <float> modelNormal;
    std::vector <float> modelUV;
    std::vector <uint16_t> modelIndexVertex;
    std::vector <uint16_t> modelIndexNormal;
    std::vector <uint16_t> modelIndexUV;
    
    MTL::Buffer* modelBufferVertex = nullptr;
    MTL::Buffer* modelBufferNormal = nullptr;
    MTL::Buffer* modelBufferUV = nullptr;
    MTL::Buffer* modelBufferIndexVertex = nullptr;
    MTL::Buffer* modelBufferIndexNormal = nullptr;
    MTL::Buffer* modelBufferIndexUV = nullptr;
    
    Texture* texture = nullptr;
    
};

#endif /* Geometry_hpp */
