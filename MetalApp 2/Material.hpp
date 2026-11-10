//
//  Material.hpp
//  MetalApp 2
//
//  Created by Macbook on 22.10.2026.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <simd/simd.h>

struct MaterialData
{
    simd::float3 ambient;
    simd::float3 diffuse;
    simd::float3 specular;
    float shininess;
};

class Material
{
public:
    Material();
    ~Material();
    
    void CreateMaterial(simd::float3 Ka,simd::float3 Kd, simd::float3 Ks,simd::float3 Ke, simd::float3 Tf, float Ns, float Ni, float d, float Tr);
    
    MaterialData GetData();
    
private:
    simd::float3 ambient = {0.2f, 0.2f, 0.2f}; //цвет фонового освещения
    simd::float3 diffese = {0.8f, 0.8f, 0.8f}; //цвет диффуз отражения
    simd::float3 specular = {0.2f, 0.2f, 0.2f}; //цвет зеркал отражения
    simd::float3 emissive = {0.0f, 0.0f, 0.0f}; //цвет собсвенного свечения.
    simd::float3 transmissionFilter = {1.0f, 1.0f, 1.0f}; //цветовой фильтр проходящего света
    
    float specularExpent = 1.0f; //степень блеска
    float opticalDensity = 1.0f; //показатель преломления света
    float dissolve = 1.0f; //непрозрачность материала
    float transparency = 0.0f; //прозрачность
    
};
#endif /* Material_hpp */
