//
//  Matrix.h
//  MetalApp 2
//
//  Created by Macbook on 04.10.2026.
//

#include "Matrix.hpp"

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}



matrix_float4x4 Matrix::MakeTranslation(float x, float y, float z)
{
    return matrix_float4x4
    {
        simd_make_float4(1.0f, 0.0f, 0.0f, 0.0f),
        simd_make_float4(0.0f, 1.0f, 0.0f, 0.0f),
        simd_make_float4(0.0f, 0.0f, 1.0f, 0.0f),
        simd_make_float4(x, y, z, 1)
    };
}
matrix_float4x4 Matrix::MakeRotation(float x, float y, float z)
{
    matrix_float4x4 rotationX = MakeRotationX(x);
    matrix_float4x4 rotationY = MakeRotationY(y);
    matrix_float4x4 rotationZ = MakeRotationZ(z);
    
    return simd_mul(simd_mul(rotationX, rotationY), rotationZ);
}

matrix_float4x4 Matrix::MakeRotationX(float angle)
{
    float a = angle * M_PI / 180.0f; //перевод из градусов в радианы
    float c = cos(a);
    float s = sin(a);

    return matrix_float4x4
    {
        simd_make_float4(1, 0.0f, 0.0f, 0.0f),
        simd_make_float4(0.0f, c, s, 0.0f),
        simd_make_float4(0.0f, -s,  c, 0.0f),
        simd_make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

matrix_float4x4 Matrix::MakeRotationY(float angle)
{
    float a = angle * M_PI / 180.0f; //перевод из градусов в радианы
    float c = cos(a);
    float s = sin(a);

    return matrix_float4x4
    {
        simd_make_float4( c,   0.0f,  -s,  0.0f),
        simd_make_float4(0.0f, 1.0f, 0.0f, 0.0f),
        simd_make_float4( s,   0.0f,  c,   0.0f),
        simd_make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

matrix_float4x4 Matrix::MakeRotationZ(float angle)
{
    float a = angle * M_PI / 180.0f; //перевод из градусов в радианы
    float c = cos(a);
    float s = sin(a);

    return matrix_float4x4
    {
        simd_make_float4(c, -s, 0.0f, 0.0f),
        simd_make_float4(s, c, 0.0f, 0.0f),
        simd_make_float4(0.0f, 0.0f,  1, 0.0f),
        simd_make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

matrix_float4x4 Matrix::MakeScale(float x, float y, float z)
{
    return matrix_float4x4
    {
        simd_make_float4(x, 0.0f, 0.0f, 0.0f),
        simd_make_float4(0.0f, y, 0.0f, 0.0f),
        simd_make_float4(0.0f, 0.0f, z, 0.0f),
        simd_make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

matrix_float4x4 Matrix::LookAt(simd::float3 CameraPosition, simd::float3 CameraTarget, simd::float3 CameraUp)
{
    simd::float3 Forward = simd::normalize(CameraTarget - CameraPosition);
    simd::float3 Right = simd::normalize(simd::cross(Forward, CameraUp));
    simd::float3 Up = simd::cross(Right, Forward);
    
    simd::float3 Backward = -Forward;
    return matrix_float4x4
    {
        simd_make_float4(Right.x, Up.x, Backward.x, 0.0f),
        simd_make_float4(Right.y, Up.y, Backward.y, 0.0f),
        simd_make_float4(Right.z, Up.z,  Backward.z, 0.0f),
        simd_make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
    
}

matrix_float4x4 Matrix::MoveTo(simd::float3 CameraPosition)
{
    return matrix_float4x4
    {
        simd_make_float4(1, 0.0f, 0.0f, 0.0f),
        simd_make_float4(0.0f, 1.0f, 0, 0.0f),
        simd_make_float4(0.0f, 0.0f,  1, 0.0f),
        simd_make_float4(-CameraPosition.x, -CameraPosition.y, -CameraPosition.z, 1.0f)
    };
};
matrix_float4x4 Matrix::ViewMatrix(simd::float3 CameraPosition, simd::float3 CameraTarget, simd::float3 CameraUp)
{
    return simd_mul(LookAt(CameraPosition, CameraTarget, CameraUp), MoveTo(CameraPosition));
}

matrix_float4x4 Matrix::ProjectionMatrix(int width, int height,unsigned int FOV, float near, float far)
{
    float a;
    float b;
    float c;
    float d;
    
    float radians = FOV * M_PI / 180.0f;
    
    if(FOV <= 0 || FOV >= 180)
    {
        std::cout <<  "Неправильно задан FOV для камеры";
    }
    float aspectRatio = static_cast<float>(width) / height;
    
    a = 1 / (aspectRatio * simd::tan(radians/2));
    b = 1 / (simd::tan(radians/2));
    c = far / (near - far);
    d = near * far/ (near - far);
            
    return matrix_float4x4
    {
        simd_make_float4(a, 0.0f, 0.0f, 0.0f),
        simd_make_float4(0.0f, b, 0.0f, 0.0f),
        simd_make_float4(0.0f, 0.0f, c, -1.0f),
        simd_make_float4(0.0f, 0.0f, d, 0.0f)
    };
}

