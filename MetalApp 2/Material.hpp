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

class Material
{
public:
    Material();
    ~Material();
private:
    simd::float3 Ambient; //цвет фонового освещения
    simd::float3 Diffese; //цвет диффуз отражения
    simd::float3 Specular; //цвет зеркал отражения
    simd::float3 Emissive; //цвет собсвенного свечения.
    
    float SpecularExpent; //степень блеска
    float OpticalDensity; //показатель преломления света
    float Dissolve; //непрозрачность материала
    float Transparency; //прозрачность
    float TransmissionFilter; //цветовой фильтр проходящего света
};
#endif /* Material_hpp */
