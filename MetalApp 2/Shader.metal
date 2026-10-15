//
//  Shader.metal
//  MetalApp 2
//
//  Created by Macbook on 26.03.2026.
//

#include <metal_stdlib>
using namespace metal;

//vertex - функция запускающая для каждой вершины
//tringleVertices - координаты вершин треугольника
struct VertexOut
{
    float4 position [[position]];
    float3 normal;
};


//получения позиции вершин на экране
[[vertex]] VertexOut vertexShader(constant float *tringleVertices [[buffer(0)]],
                               constant float4x4 *modelMatrix [[buffer(1)]],
                               constant float4x4 *viewMatrix [[buffer(2)]],
                               constant float4x4 *projectionMatrix[[buffer(3)]],
                               constant float *normalVertices [[buffer((4))]],
                               constant ushort *vertexIndex[[buffer (5)]],
                               constant ushort *normalIndex[[buffer (6)]],
                               ushort id[[vertex_id]])
{
    
    uint v = uint(vertexIndex[id]) * 3;
    uint n = uint(normalIndex[id]) * 3;

    const float positionX = tringleVertices[v];
    const float positionY = tringleVertices[v + 1];
    const float positionZ = tringleVertices[v + 2];
    
    float4 position = float4(positionX, positionY, positionZ, 1.0f);
    
    const float normalX = normalVertices[n];
    const float normalY = normalVertices[n + 1];
    const float normalZ = normalVertices[n + 2];
    
    float3 normal = float3(normalX, normalY, normalZ);
    
    float4 appliedModelMatrix = (*modelMatrix) * position;
    float4 appliedViewMatrix = (*viewMatrix) * appliedModelMatrix;
    float4 appliedProjectionMatrix = (*projectionMatrix) * appliedViewMatrix;

    //return appliedProjectionMatrix;
    
    //Применение модель матрицы на  нормали
    float3x3 normalMatrix = float3x3((*modelMatrix)[0].xyz,(*modelMatrix)[1].xyz,(*modelMatrix)[2].xyz);
    
    VertexOut out;
        out.position = appliedProjectionMatrix;
        out.normal = normalize(normalMatrix * normal);
        return out;
}

fragment float4 fragmentShader(VertexOut in [[stage_in]],
                               constant float4 *color [[buffer(0)]])
{
    float3 normal = normalize(in.normal);
    float Intensive = 2.0f;

    float3 lightDirection = normalize(float3(0.25f, 1.0f, 0.5f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float3 finalColor = color->rgb * diffuse * Intensive;

    return float4(finalColor, color->a);
}
