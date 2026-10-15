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
    std::ifstream fileModel("Assets/Models/" + nameFileModel + ".obj");
    if(!fileModel.is_open())
    {
        std::cout << "Не удалось открыть модель" << std::endl;
        return;
    }
    std::string line; //строка
    
    modelVertex.clear();
    modelIndexVertex.clear();
    
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
            }
            
        }
        if (type == "f")
        {
            std::vector<uint16_t> faceIndicesVertex;
            std::vector<uint16_t> faceIndicesNormal;
            std::string indexString;

            while (stream >> indexString)
            {
                size_t pos = indexString.find('/');
                size_t normal = indexString.find('/', pos + 1);
                
                std::string indexVertexString = indexString.substr(0, pos);
                std::string indexNormalString = indexString.substr(normal+1);

                uint16_t vertexIndex = std::stoi(indexVertexString) - 1;
                uint16_t normalIndex = std::stoi(indexNormalString) - 1;
                
                faceIndicesVertex.push_back(vertexIndex);
                faceIndicesNormal.push_back(normalIndex);
            }

            for (size_t i = 1; i + 1 < faceIndicesVertex.size(); i++)
            {
                modelIndexVertex.push_back(faceIndicesVertex[0]);
                modelIndexVertex.push_back(faceIndicesVertex[i]);
                modelIndexVertex.push_back(faceIndicesVertex[i + 1]);
            }
            for (size_t i = 1; i+1 < faceIndicesNormal.size(); i++)
            {
                modelIndexNormal.push_back(faceIndicesNormal[0]);
                modelIndexNormal.push_back(faceIndicesNormal[i]);
                modelIndexNormal.push_back(faceIndicesNormal[i+1]);
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
std::vector <uint16_t> Parser::GetModelIndexVertex()
{
    return modelIndexVertex;
}
std::vector <uint16_t> Parser::GetModelIndexNormal()
{
    return modelIndexNormal;
}
Parser::~Parser()
{
    
}

