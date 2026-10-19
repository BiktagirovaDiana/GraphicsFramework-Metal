//
//  Geometry.hpp
//  MetalApp 2
//
//  Created by Macbook on 03.10.2026.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include "Metal/Metal.hpp"
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
    Geometry();
    ~Geometry();
    
    MTL::Buffer* CreateTriangleBuffer(MTL::Device* device);
    MTL::Buffer* CreateSquareBuffer(MTL::Device* device);
    MTL::Buffer* CreateCubeBuffer(MTL::Device* device);
    MTL::Buffer* CreatePlaneBuffer(MTL::Device* device);
    
    
    void SetModelVertex(MTL::Device* device, std::vector <float> Vertex);
    void SetModelNormal(MTL::Device* device, std::vector <float> Normal);
    void SetModelUV(MTL::Device* device, std::vector <float> UV);
    void SetModelIndexVertex(MTL::Device* device, std::vector <uint16_t> Index);
    void SetModelIndexNormal(MTL::Device* device, std::vector <uint16_t> Index);
    void SetModelIndexUV(MTL::Device* device, std::vector <uint16_t> Index);

    
    
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

    
private:
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
    
};

#endif /* Geometry_hpp */
