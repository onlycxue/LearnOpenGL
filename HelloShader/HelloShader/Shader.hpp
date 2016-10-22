//
//  Shader.hpp
//  HelloShader
//
//  Created by playcrab on 16/10/18.
//  Copyright © 2016年 playcrab. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <iostream>
#include <stdio.h>
#include "GL/glew.h"

class Shader{
    
    Shader(std::string verFilePath,std::string fragFilePath);
    void use();
    
private:
    GLint _program;
};



#endif /* Shader_hpp */
