//
//  Shader.cpp
//  HelloShader
//
//  Created by playcrab on 16/10/18.
//  Copyright © 2016年 playcrab. All rights reserved.
//

#include "Shader.hpp"
#include <fstream>
#include <sstream>


Shader::Shader(std::string verFilePath,std::string fragFilePath)
{
    
    
    std::string vertexCode;
    std::string fragmentCode;
    
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    
    try{
        vShaderFile.open(verFilePath);
        fShaderFile.open(fragFilePath);
        
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
    }catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    
    
    GLint verShader,fragShader;
    
    verShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(GL_VERTEX_SHADER,1,&vShaderCode,NULL);
    glCompileShader(verShader);
    
    GLint isSuccess;
    glGetShaderiv(verShader,GL_COMPILE_STATUS,&isSuccess);
    
    GLchar infoBuf[512];
    if(!isSuccess){
        glGetShaderInfoLog(verShader,512,NULL,infoBuf);
        std::cout << infoBuf << std::endl;
    }
    
    
    fragShader =  glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(GL_FRAGMENT_SHADER,1,&fShaderCode,NULL);
    glCompileShader(fragShader);
    
    GLint glProgram;
    
    glProgram = glCreateProgram();
    glAttachShader(glProgram,verShader);
    glAttachShader(glProgram,fragShader);
    glLinkProgram(glProgram);
    
    glGetProgramiv(glProgram,GL_LINK_STATUS,&isSuccess);
    
    if(!isSuccess){
        glGetProgramInfoLog(fragShader,512,NULL,infoBuf);
        std::cout << infoBuf << std::endl;
    }
    
    glDeleteShader(verShader);
    glDeleteShader(fragShader);
    
    this->_program = glProgram;
    
}

void Shader::use()
{
    glUseProgram(this->_program);
}