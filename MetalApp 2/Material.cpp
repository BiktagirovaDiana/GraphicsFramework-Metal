//
//  Material.cpp
//  MetalApp 2
//
//  Created by Macbook on 22.10.2026.
//

#include "Material.hpp"

Material::Material()
{
    
}

Material::~Material()
{
    
}



void Material::CreateMaterial(simd::float3 Ka,simd::float3 Kd, simd::float3 Ks,simd::float3 Ke, simd::float3 Tf, float Ns, float Ni, float d, float Tr)
{
    ambient = Ka;
    diffese = Kd;
    specular = Ks;
    emissive = Ke;
    transmissionFilter = Tf;
    
    specularExpent = Ns;
    opticalDensity = Ni;
    dissolve = d;
    transparency = Tr;
}
