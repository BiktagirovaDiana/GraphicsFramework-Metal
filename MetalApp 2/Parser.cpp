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
    modelIndex.clear();
    
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
        if (type == "f")
        {
            std::vector<uint16_t> faceIndices;
            std::string vertex;

            while (stream >> vertex)
            {
                size_t pos = vertex.find('/');
                std::string index = vertex.substr(0, pos);

                uint16_t vertexIndex = std::stoi(index) - 1;
                faceIndices.push_back(vertexIndex);
            }

            for (size_t i = 1; i + 1 < faceIndices.size(); i++)
            {
                modelIndex.push_back(faceIndices[0]);
                modelIndex.push_back(faceIndices[i]);
                modelIndex.push_back(faceIndices[i + 1]);
            }
        }
    }
    
}
std::vector <float> Parser::GetModelVertex()
{
    return modelVertex;
}
std::vector <uint16_t> Parser::GetModelIndex()
{
    return modelIndex;
}
Parser::~Parser()
{
    
}

