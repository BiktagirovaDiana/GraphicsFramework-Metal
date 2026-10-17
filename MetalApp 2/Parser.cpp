//
//  Parser.cpp
//  MetalApp 2
//
//  Created by Macbook on 12.10.2026.
//

#include "Parser.hpp"

Parser::Parser()
{
    
}
void Parser::OpenModel(std::string nameFileModel)
{
    isNormal = false;
    
    std::ifstream fileModel("Assets/Models/" + nameFileModel + ".obj");
    if(!fileModel.is_open())
    {
        std::cout << "Не удалось открыть модель" << std::endl;
        return;
    }
    std::string line; //строка
    
    modelVertex.clear();
    modelIndexVertex.clear();
    modelNormal.clear();
    modelIndexNormal.clear();
    modelUV.clear();
    
    while(std::getline(fileModel, line))
    {
        std::istringstream stream(line);
        std::string type; //тип данных в obj
        stream >> type;
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
    
}
std::vector <float> Parser::GetModelVertex()
{
    return modelVertex;
}
std::vector <float> Parser::GetModelNormal()
{
    return modelNormal;
}
std::vector <float> Parser::GetModelUV()
{
    return modelUV;
}
std::vector <uint16_t> Parser::GetModelIndexVertex()
{
    return modelIndexVertex;
}
std::vector <uint16_t> Parser::GetModelIndexNormal()
{
    return modelIndexNormal;
}
std::vector <uint16_t> Parser::GetModelIndexUV()
{
    return modelIndexUV;
}
Parser::~Parser()
{
    
}

