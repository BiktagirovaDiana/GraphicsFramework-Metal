//
//  Matrix.hpp
//  MetalApp 2
//
//  Created by Macbook on 04.10.2026.
//

#include "Metal/Metal.hpp"
#include <simd/simd.h>
#include <cmath>
#include <iostream>

class Matrix
{
public:
    Matrix();
    ~Matrix();
    //Model Matrix
    matrix_float4x4 MakeRotation(float x, float y, float z);
    matrix_float4x4 MakeRotationX(float angle);
    matrix_float4x4 MakeRotationY(float angle);
    matrix_float4x4 MakeRotationZ(float angle);
    
    //View Matrix
    matrix_float4x4 LookAt(simd::float3 CameraPosition, simd::float3 CameraTarget, simd::float3 CameraUp);
    matrix_float4x4 MoveTo(simd::float3 CameraPosition);
    matrix_float4x4 ViewMatrix(simd::float3 CameraPosition, simd::float3 CameraTarget, simd::float3 CameraUp);
    
    //Projection Matrix
    matrix_float4x4 ProjectionMatrix(int width, int heigh,unsigned int FOV, float near, float far);
};
