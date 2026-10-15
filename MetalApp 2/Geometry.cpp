//
//  Geometry.cpp
//  MetalApp 2
//
//  Created by Macbook on 03.10.2026.
//

#include "Geometry.hpp"

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}
MTL::Buffer* Geometry::CreateTriangleBuffer(MTL::Device* device)
{
    
    float triangleVertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    //возвращаем данные вершин треугольника для буффера
    return device->newBuffer(triangleVertices,sizeof(triangleVertices),MTL::ResourceStorageModeShared);
}
MTL::Buffer* Geometry::CreateSquareBuffer(MTL::Device* device)
{
    float squareVertices[] =
    {
        0.5f,  0.5f, 0.0f,
       -0.5f, 0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        
        0.5f,  0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
    };
    
    //возвращаем данные вершин треугольника для буффера
    return device->newBuffer(squareVertices,sizeof(squareVertices),MTL::ResourceStorageModeShared);
}

MTL::Buffer* Geometry::CreateCubeBuffer(MTL::Device* device)
{
    float cubeVertices[] =
    {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };
    return device->newBuffer(cubeVertices, sizeof(cubeVertices), MTL::ResourceStorageModeShared);
}

void Geometry::CreateModelVertexBuffer(MTL::Device* device, std::vector <float> modelVertex)
{
    modelBufferVertex = device->newBuffer(modelVertex.data(),modelVertex.size() * sizeof(float), MTL::ResourceStorageModeShared);
}
void Geometry::CreateModelNormalBuffer(MTL::Device* device, std::vector <float> modelNormal)
{
    modelBufferNormal = device->newBuffer(modelNormal.data(), modelNormal.size() * sizeof(float), MTL::ResourceStorageModeShared);
}
void Geometry::CreateModelIndexVertexBuffer(MTL::Device* device, std::vector <uint16_t> modelIndex)
{
    modelBufferIndexVertex = device->newBuffer(modelIndex.data(), modelIndex.size() *
        sizeof(uint16_t), MTL::ResourceStorageModeShared);
}
void Geometry::CreateModelIndexNormalBuffer(MTL::Device* device, std::vector <uint16_t> modelIndex)
{
    modelBufferIndexNormal = device->newBuffer(modelIndex.data(), modelIndex.size() *
        sizeof(uint16_t), MTL::ResourceStorageModeShared);
}


MTL::Buffer* Geometry::GetModelBufferVertex()
{
    return modelBufferVertex;
}

MTL::Buffer* Geometry::GetModelBufferNormal()
{
    return modelBufferNormal;
}
MTL::Buffer* Geometry::GetModelBufferIndexVertex()
{
    return modelBufferIndexVertex;
}

MTL::Buffer* Geometry::GetModelBufferIndexNormal()
{
    return modelBufferIndexNormal;
}

void Geometry::SetModelVertex(std::vector <float> Vertex)
{
    modelVertex = Vertex;
}
void Geometry::SetModelNormal(std::vector<float> Normal)
{
    modelNormal = Normal;
}
void Geometry::SetModelIndexVertex(std::vector <uint16_t> Index)
{
    modelIndexVertex = Index;
}
void Geometry::SetModelIndexNormal(std::vector <uint16_t> Index)
{
    modelIndexNormal = Index;
}
std::vector<float> Geometry::GetModelVertex()
{
    return modelVertex;
}

std::vector<float> Geometry::GetModelNormal()
{
    if(modelNormal.empty())
    {
        CreateNormal();
    }
    return modelNormal;
}

std::vector<uint16_t> Geometry::GetModelIndexVertex()
{
    if(modelNormal.empty())
    {
        CreateNormal();
    }
    return modelIndexVertex;
}

std::vector<uint16_t> Geometry::GetModelIndexNormal()
{
    return modelIndexNormal;
}

void Geometry::CreateNormal()
{
    
    std::vector <simd::float3> positionVertex;
    for (int i = 1; i != modelVertex.size() + 1; i++)
    {
        if(i % 3 == 0)
        {
            
            simd::float3 position =
            {
                modelVertex[i-3], modelVertex[i-2], modelVertex[i-1]
            };
            
            positionVertex.push_back(position);
        }
    }
    for(int i = 1; i != modelIndexVertex.size(); i++)
    {
        if(i % 3 == 0)
        {
            simd::float3 A = positionVertex[modelIndexVertex[i-3]];
            simd::float3 B = positionVertex[modelIndexVertex[i-2]];
            simd::float3 C = positionVertex[modelIndexVertex[i-1]];
            
            simd::float3 AB = B - A;
            simd::float3 AC = C - A;
            
            simd::float3 N = simd_normalize(simd::cross(AB, AC));
            
            modelNormal.push_back(N.x);
            modelNormal.push_back(N.y);
            modelNormal.push_back(N.z);
            
            modelIndexNormal.push_back((i-1)/3);
            modelIndexNormal.push_back((i-1)/3);
            modelIndexNormal.push_back((i-1)/3);
        }
    }
    
}

