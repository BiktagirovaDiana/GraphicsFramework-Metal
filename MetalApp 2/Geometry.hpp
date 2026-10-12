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
    MTL::Buffer* CreateModelBuffer(MTL::Device* device, std::vector <float> modelVertex);
    
    uint16_t indices[36] =
    {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Back
        4, 6, 5,
        4, 7, 6,

        // Left
        0, 3, 7,
        0, 7, 4,

        // Right
        1, 5, 6,
        1, 6, 2,

        // Top
        3, 2, 6,
        3, 6, 7,

        // Bottom
        0, 4, 5,
        0, 5, 1
    };
    
    //std::vector <float> modelVertex;
    //std::vector <uint16_t> modelIndex;
    
};

#endif /* Geometry_hpp */
