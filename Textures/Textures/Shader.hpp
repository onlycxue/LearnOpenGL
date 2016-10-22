//
//  Shader.hpp
//  Textures
//
//  Created by playcrab on 16/10/20.
//  Copyright © 2016年 playcrab. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

#include "GL/glew.h"
#include <iostream>

class Shader {
    
public:
    Shader(std::string vertexPath,std::string fragmentPath);
    void use();
    GLint getProgram();
private:
    
    GLint _program;
    
};






#endif /* Shader_hpp */
