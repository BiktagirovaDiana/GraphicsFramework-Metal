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
    void OpenModelOBJ(std::string nameFileModel, Geometry* geometry);
    void OpenModelMTL(std::string nameFileModel);
    
private:
    bool isNormal;
    std::string nameFileMTL;
    
};
#endif /* Parser_hpp */
