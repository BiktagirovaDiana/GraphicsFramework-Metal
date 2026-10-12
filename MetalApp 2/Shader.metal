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


//получения позиции вершин на экране
[[vertex]] float4 vertexShader(constant float *tringleVertices [[buffer(0)]],
                               constant float4x4 *modelMatrix [[buffer(1)]],
                               constant float4x4 *viewMatrix [[buffer(2)]],
                               constant float4x4 *projectionMatrix[[buffer(3)]],
                               ushort vertexIndex[[vertex_id]])
{
    ushort i = vertexIndex * 3;
    
    const float x = tringleVertices[i];
    const float y = tringleVertices[i + 1];
    const float z = tringleVertices[i + 2];
    
    float4 position = float4(x, y, z, 1.0f);
    
    float4 appliedModelMatrix = (*modelMatrix) * position;
    float4 appliedViewMatrix = (*viewMatrix) * appliedModelMatrix;
    float4 appliedProjectionMatrix = (*projectionMatrix) * appliedViewMatrix;

    return appliedProjectionMatrix;
}

fragment float4 fragmentShader(uint primitiveId [[primitive_id]],
                               constant float4 *faceColors [[buffer(0)]])
{
    uint faceId = primitiveId / 2; // 2 треугольника = 1 сторона куба
    return faceColors[faceId];
}
