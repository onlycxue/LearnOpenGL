//
//  Shader.cpp
//  Textures
//
//  Created by playcrab on 16/10/20.
//  Copyright © 2016年 playcrab. All rights reserved.
//

#include "Shader.hpp"
#include <fstream>
#include <istream>
#include <streambuf>
#include <string>
#include <sstream>

Shader::Shader(std::string vertexPath,std::string fragmentPath)
{
    
    std::ifstream vertexFstream,fragmentFstream;
    
    std::string vertexSrc,fragmentSrc;
    
    try {
        
   
            vertexFstream.open(vertexPath);
            fragmentFstream.open(fragmentPath);
        
            std::stringstream vertexBuf;
            vertexBuf << vertexFstream.rdbuf();
    
            std::stringstream fragmentBuf;
            fragmentBuf << fragmentFstream.rdbuf();
    
        
            vertexSrc = vertexBuf.str();
            fragmentSrc = fragmentBuf.str();
        
        
    }catch(std::fstream::failure e){
        std::cout << "ERROR::SHADER_FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    
    const GLchar* vertexCode = vertexSrc.c_str();
    const GLchar* fragmentCode = fragmentSrc.c_str();
    
    
    GLint vertexShader,fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexCode,0);
    glCompileShader(vertexShader);
    
    GLint isOk;
    GLchar infoBuf[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&isOk);
    
    if (!isOk){
        
        glGetShaderInfoLog(vertexShader,512,NULL,infoBuf);
        
        std::cout << infoBuf << std::endl;
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentCode,0);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&isOk);
    
    if(!isOk){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoBuf);
        std::cout << infoBuf << std::endl;
    }
    
    this->_program = glCreateProgram();
    
    glAttachShader(this->_program,vertexShader);
    glAttachShader(this->_program,fragmentShader);
    
    glLinkProgram(this->_program);
    
    glGetProgramiv(this->_program,GL_LINK_STATUS,&isOk);
    
    if(!isOk)
    {
        glGetProgramInfoLog(this->_program,512,NULL,infoBuf);
        
        std::cout << infoBuf << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    
}

void Shader::use()
{
    glUseProgram(this->_program);
}

GLint Shader::getProgram()
{
    return this->_program;
}

