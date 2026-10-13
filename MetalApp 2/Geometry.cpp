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
void Geometry::CreateModelIndexBuffer(MTL::Device* device, std::vector <uint16_t> modelIndex)
{
    modelBufferIndex = device->newBuffer(modelIndex.data(), modelIndex.size() *
        sizeof(uint16_t), MTL::ResourceStorageModeShared);
}

MTL::Buffer* Geometry::GetModelBufferVertex()
{
    return modelBufferVertex;
}
MTL::Buffer* Geometry::GetModelBufferIndex()
{
    return modelBufferIndex;
}

void Geometry::SetModelVertex(std::vector <float> Vertex)
{
    modelVertex = Vertex; 
}
void Geometry::SetModelIndex(std::vector <uint16_t> Index)
{
    modelIndex = Index;
}
std::vector<float> Geometry::GetModelVertex()
{
    return modelVertex;
}

std::vector<uint16_t> Geometry::GetModelIndex()
{
    return modelIndex;
}


