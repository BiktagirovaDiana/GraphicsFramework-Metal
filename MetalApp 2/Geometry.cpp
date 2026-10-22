//
//  Geometry.cpp
//  MetalApp 2
//
//  Created by Macbook on 03.10.2026.
//

#include "Geometry.hpp"

Geometry::Geometry(MTL::Device* device) : device(device)
{
    
}

Geometry::~Geometry()
{
    if(modelBufferVertex)
    {
        modelBufferVertex->release();
    }
    if(modelBufferNormal)
    {
        modelBufferNormal->release();
    }
    if(modelBufferUV)
    {
        
        modelBufferUV->release();
    }
    if(modelBufferIndexVertex)
    {
        modelBufferIndexVertex->release();
    }
    if(modelBufferIndexNormal)
    {
        modelBufferIndexNormal->release();
    }
    
    if(modelBufferIndexUV)
    {
        modelBufferIndexUV->release();
    }
    if(!modelVertex.empty())
    {
        modelVertex.clear();
    }
    if(!modelNormal.empty())
    {
        modelNormal.clear();
    }
    if(!modelUV.empty())
    {
        modelUV.clear();
    }
    if(!modelIndexVertex.empty())
    {
        modelIndexVertex.clear();
    }
    if(!modelIndexNormal.empty())
    {
        modelIndexNormal.clear();
    }
    if(!modelIndexUV.empty())
    {
        modelIndexUV.clear();
    }
    
}
MTL::Buffer* Geometry::CreateTriangleBuffer()
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
MTL::Buffer* Geometry::CreateSquareBuffer()
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

MTL::Buffer* Geometry::CreateCubeBuffer()
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


MTL::Buffer* Geometry::GetModelBufferVertex()
{
    return modelBufferVertex;
}

MTL::Buffer* Geometry::GetModelBufferNormal()
{
    return modelBufferNormal;
}
MTL::Buffer* Geometry::GetModelBufferUV()
{
    return modelBufferUV;
}
MTL::Buffer* Geometry::GetModelBufferIndexVertex()
{
    return modelBufferIndexVertex;
}

MTL::Buffer* Geometry::GetModelBufferIndexNormal()
{
    return modelBufferIndexNormal;
}
MTL::Buffer* Geometry::GetModelBufferIndexUV()
{
    return modelBufferIndexUV;
}

void Geometry::SetModelVertex(std::vector <float> Vertex)
{
    if (modelBufferVertex)
       {
           modelBufferVertex->release();
           modelBufferVertex = nullptr;
       }
    
    modelVertex = Vertex;
    modelBufferVertex = device->newBuffer(modelVertex.data(),modelVertex.size() * sizeof(float), MTL::ResourceStorageModeShared);

}
void Geometry::SetModelNormal(std::vector<float> Normal)
{
    if(modelBufferNormal)
    {
        modelBufferNormal->release();
        modelBufferNormal= nullptr;
    }
    
    modelNormal = Normal;
    if(Normal.empty())
    {
        CreateNormal();
    }
    
    modelBufferNormal = device->newBuffer(modelNormal.data(), modelNormal.size() * sizeof(float), MTL::ResourceStorageModeShared);
}
void Geometry::SetModelUV(std::vector<float> UV)
{
    if(modelBufferUV)
    {
        modelBufferUV->release();
        modelBufferUV=nullptr;
    }
    modelUV = UV;
    modelBufferUV = device->newBuffer(modelUV.data(), modelUV.size() * sizeof(float), MTL::ResourceStorageModeShared);
}
void Geometry::SetModelIndexVertex(std::vector <uint16_t> Index)
{
    if(modelBufferIndexVertex)
    {
        modelBufferIndexVertex->release();
        modelBufferIndexVertex=nullptr;
    }
    modelIndexVertex = Index;
    modelBufferIndexVertex = device->newBuffer(modelIndexVertex.data(), modelIndexVertex.size() * sizeof(uint16_t), MTL::ResourceStorageModeShared);
}
void Geometry::SetModelIndexNormal(std::vector <uint16_t> Index)
{
    if(modelBufferIndexNormal)
    {
        modelBufferIndexNormal->release();
        modelBufferIndexNormal=nullptr;
    }
    modelIndexNormal = Index;
    if(Index.empty())
    {
        CreateNormal();
    }
    modelBufferIndexNormal = device->newBuffer(modelIndexNormal.data(), modelIndexNormal.size() * sizeof(uint16_t), MTL::ResourceStorageModeShared);
}

void Geometry::SetModelIndexUV(std::vector <uint16_t> Index)
{
    if(modelBufferIndexUV)
    {
        modelBufferIndexUV->release();
        modelBufferIndexUV=nullptr;
    }
    modelIndexUV = Index;
    modelBufferIndexUV = device->newBuffer(modelIndexUV.data(), modelIndexUV.size() * sizeof(uint16_t), MTL::ResourceStorageModeShared);
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

std::vector<float> Geometry::GetModelUV()
{

    return modelUV;
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
std::vector<uint16_t> Geometry::GetModelIndexUV()
{
    return modelIndexUV;
}

void Geometry::CreateNormal()
{
    if(!modelNormal.empty())
    {
        modelNormal.clear();
    }
    if(!modelIndexNormal.empty())
    {
        modelIndexNormal.clear();
    }
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
    modelBufferNormal = device->newBuffer(modelNormal.data(), modelNormal.size() * sizeof(float), MTL::ResourceStorageModeShared);
    modelBufferIndexNormal = device->newBuffer(modelIndexNormal.data(), modelIndexNormal.size() * sizeof(uint16_t), MTL::ResourceStorageModeShared);
}

void Geometry::ClearAll()
{
    
    modelVertex.clear();
    modelNormal.clear();
    modelUV.clear();
    modelIndexVertex.clear();
    modelIndexNormal.clear();
    modelIndexUV.clear();
    
    if(!(modelBufferVertex == nullptr))
    {
        modelBufferVertex->release();
    }
    if(!(modelBufferNormal == nullptr))
    {
        modelBufferNormal->release();
    }
    if(!(modelBufferUV == nullptr))
    {
        modelBufferUV->release();
    }
    if(!(modelBufferIndexVertex == nullptr))
    {
        modelBufferIndexVertex->release();
    }
    if(!(modelBufferIndexNormal == nullptr))
    {
        modelBufferIndexNormal->release();
    }
    if(!(modelBufferIndexUV == nullptr))
    {
        modelBufferIndexUV->release();
    }
};

