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
    
    void CreateModelVertexBuffer(MTL::Device* device, std::vector <float> modelVertex);
    void CreateModelNormalBuffer(MTL::Device* device, std::vector <float> modelNormal);
    void CreateModelIndexVertexBuffer(MTL::Device* device, std::vector <uint16_t> modelIndexVertex);
    void CreateModelIndexNormalBuffer(MTL::Device* device, std::vector <uint16_t> modelIndexVertex);
    
    void SetModelVertex(std::vector <float> Vertex);
    void SetModelNormal(std::vector <float> Normal);
    void SetModelIndexVertex(std::vector <uint16_t> Index);
    void SetModelIndexNormal(std::vector <uint16_t> Index);
    
    std::vector<float> GetModelVertex();
    std::vector<float> GetModelNormal();
    std::vector<uint16_t> GetModelIndexVertex();
    std::vector<uint16_t> GetModelIndexNormal();
    
    MTL::Buffer* GetModelBufferVertex();
    MTL::Buffer* GetModelBufferNormal();
    MTL::Buffer* GetModelBufferIndexVertex();
    MTL::Buffer* GetModelBufferIndexNormal();
    

    
private:
    std::vector <float> modelVertex;
    std::vector <float> modelNormal;
    std::vector <uint16_t> modelIndexVertex;
    std::vector <uint16_t> modelIndexNormal;
    
    MTL::Buffer* modelBufferVertex;
    MTL::Buffer* modelBufferNormal;
    MTL::Buffer* modelBufferIndexVertex;
    MTL::Buffer* modelBufferIndexNormal;
    
    
};

#endif /* Geometry_hpp */
