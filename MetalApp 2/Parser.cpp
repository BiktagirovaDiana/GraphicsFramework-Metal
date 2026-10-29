//
//  Parser.cpp
//  MetalApp 2
//
//  Created by Macbook on 12.10.2026.
//

#include "Parser.hpp"

Parser::Parser(MTL::Device* device) : device(device)
{
    
};
void Parser::OpenModelOBJ(std::string nameFileModel, Geometry* geometry, Material* material)
{
    std::vector <float> modelVertex;
    std::vector <float> modelNormal;
    std::vector <float> modelUV;
    std::vector <uint16_t> modelIndexVertex;
    std::vector <uint16_t> modelIndexNormal;
    std::vector <uint16_t> modelIndexUV;
    
    isNormal = false;
    
    std::ifstream fileModel("Assets/Models/" + nameFileModel + ".obj");
    if(!fileModel.is_open())
    {
        std::cout << "Не удалось открыть модель" << std::endl;
        return;
    }
    std::string line; //строка
    geometry->ClearAll();

    while(std::getline(fileModel, line))
    {
        std::istringstream stream(line);
        std::string type; //тип данных в obj
        stream >> type;
        
        if(type == "mtllib")
        {
            std::string nameMTL;
            if(stream >> nameMTL)
            {
                nameFileMTL = nameMTL;
            }
        }
        if(type == "v")
        {
            float x, y, z;
            if (stream >> x >> y >> z)
            {
                modelVertex.push_back(x);
                modelVertex.push_back(y);
                modelVertex.push_back(z);
            }
        }
        if(type == "vn")
        {
            float x, y, z;
            if(stream >> x >> y >> z)
            {
                modelNormal.push_back(x);
                modelNormal.push_back(y);
                modelNormal.push_back(z);
                isNormal = true;
            }
            
        }
        if(type == "vt")
        {
            float x, y;
            if(stream >> x >> y)
            {
                modelUV.push_back(x);
                modelUV.push_back(y);
            }
        }
        
        if (type == "f")
        {
            std::vector<uint16_t> faceIndicesVertex;
            std::vector<uint16_t> faceIndicesNormal;
            std::vector<uint16_t> faceIndicesUV;

            std::string indexString;

            while (stream >> indexString)
            {
                size_t firstSlash = indexString.find('/');
                size_t secondSlash = std::string::npos;

                if (firstSlash != std::string::npos)
                {
                    secondSlash = indexString.find('/', firstSlash + 1);
                }

                // Индекс вершины
                std::string indexVertexString = indexString.substr(0, firstSlash);

                uint16_t vertexIndex = std::stoi(indexVertexString) - 1;

                faceIndicesVertex.push_back(vertexIndex);

                // Индекс UV
                if (firstSlash != std::string::npos && firstSlash + 1 < indexString.size())
                {
                    std::string indexUVString;

                    if (secondSlash == std::string::npos)
                    {
                        indexUVString = indexString.substr(firstSlash + 1);
                    }
                    else
                    {
                        indexUVString = indexString.substr(firstSlash + 1, secondSlash - firstSlash - 1);
                    }

                    if (!indexUVString.empty())
                    {
                        uint16_t UVIndex = std::stoi(indexUVString) - 1;
                        faceIndicesUV.push_back(UVIndex);
                    }
                }

                // Индекс нормали
                if (secondSlash != std::string::npos && secondSlash + 1 < indexString.size())
                {
                    std::string indexNormalString = indexString.substr(secondSlash + 1);

                    uint16_t normalIndex = std::stoi(indexNormalString) - 1;

                    faceIndicesNormal.push_back(normalIndex);

                    isNormal = true;
                }
            }

            // Триангуляция вершин
            for (size_t i = 1; i + 1 < faceIndicesVertex.size(); i++)
            {
                modelIndexVertex.push_back(faceIndicesVertex[0]);
                modelIndexVertex.push_back(faceIndicesVertex[i]);
                modelIndexVertex.push_back(faceIndicesVertex[i + 1]);
            }

            // Триангуляция нормалей
            if (faceIndicesNormal.size() == faceIndicesVertex.size())
            {
                for (size_t i = 1; i + 1 < faceIndicesNormal.size(); i++)
                {
                    modelIndexNormal.push_back(faceIndicesNormal[0]);
                    modelIndexNormal.push_back(faceIndicesNormal[i]);
                    modelIndexNormal.push_back(faceIndicesNormal[i + 1]);
                }
            }

            // Триангуляция UV
            if (faceIndicesUV.size() == faceIndicesVertex.size())
            {
                for (size_t i = 1; i + 1 < faceIndicesUV.size(); i++)
                {
                    modelIndexUV.push_back(faceIndicesUV[0]);
                    modelIndexUV.push_back(faceIndicesUV[i]);
                    modelIndexUV.push_back(faceIndicesUV[i + 1]);
                }
            }
        }
    }
    if (!nameFileMTL.empty())
    {
        OpenModelMTL(nameFileMTL, material, geometry);
    }


    geometry->SetModelVertex(modelVertex);
    geometry->SetModelIndexVertex(modelIndexVertex);
    if(modelNormal.empty())
    {
        geometry->CreateNormal();
    }
    else
    {
        geometry->SetModelNormal(modelNormal);
        geometry->SetModelIndexNormal(modelIndexNormal);
    }
    geometry->SetModelUV(modelUV);
    geometry->SetModelIndexUV(modelIndexUV);
}
void Parser::OpenModelMTL(std::string nameFileModel, Material* material, Geometry* geometry)
{
    simd::float3 Ka;
    simd::float3 Kd;
    simd::float3 Ks;
    simd::float3 Ke;
    
    float Ns;
    float Ni;
    float d;
    float Tr;
    float illum;
    float Tf;

    std::ifstream fileModel("Assets/Models/" + nameFileModel);
    if(!fileModel.is_open())
    {
        std::cout << "Не удалось открыть модель" << std::endl;
        return;
    }
    
    std::string line; //строка
    
    while(std::getline(fileModel, line))
    {
        std::istringstream stream(line);
        std::string type;
        
        stream >> type;
        
        
        if(type == "Ka")
        {
            float x, y, z;
            if (stream >> x >> y >> z)
            {
                Ka = {x, y, z};
            }
        }
        if(type == "Kd")
        {
            float x, y, z;
            if (stream >> x >> y >> z)
            {
                Kd = {x, y, z};
            }
        }
        if(type == "Ks")
        {
            float x, y, z;
            if (stream >> x >> y >> z)
            {
                Ks = {x, y, z};
            }
        }
        if(type == "Ke")
        {
            float x, y, z;
            if (stream >> x >> y >> z)
            {
                Ke = {x, y, z};
            }
        }
        if(type == "Ns")
        {
            float x;
            if (stream >> x)
            {
                Ns = x;
            }
        }
        if(type == "Ni")
        {
            float x;
            if (stream >> x)
            {
                Ni = x;
            }
        }
        if(type == "Tr")
        {
            float x;
            if (stream >> x)
            {
                Tr = x;
            }
        }
        if(type == "Tf")
        {
            float x;
            if (stream >> x)
            {
                Tf = x;
            }
        }
        if(type == "illum")
        {
            float x;
            if (stream >> x)
            {
                illum = x;
            }
        }
        if(type == "d")
        {
            float x;
            if (stream >> x)
            {
                d = x;
            }
        }
        if(type == "map_Kd")
        {
            std::string nameTexture;
            if(stream >> nameTexture)
            {
                //SetTexture(nameTexture);
                geometry->SetTexture(nameTexture);
            }
        }
    }
    
    material->CreateMaterial(Ka, Kd, Ks, Ke, Tf, Ns, Ni, d, Tr);
    
    
}

Parser::~Parser()
{
    
}

