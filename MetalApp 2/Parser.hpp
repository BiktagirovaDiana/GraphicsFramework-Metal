//
//  Parser.hpp
//  MetalApp 2
//
//  Created by Macbook on 12.10.2026.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "Geometry.hpp"

//#include <string>


class Parser
{
public:
    Parser();
    ~Parser();
    void OpenModel(std::string nameFileModel);
    std::vector <float> GetModelVertex();
    std::vector <uint16_t> GetModelIndex();
    
    Geometry geometry;
    
private:
    std::vector <float> modelVertex;
    std::vector <uint16_t> modelIndex;
};
#endif /* Parser_hpp */
