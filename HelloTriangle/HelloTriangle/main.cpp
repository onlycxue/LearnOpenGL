//
//  main.cpp
//  HelloTriangle
//
//  Created by playcrab on 16/10/11.
//  Copyright © 2016年 playcrab. All rights reserved.
//
#include <iostream>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define GLFW_WINSIZE_WIDTH 800
#define GLFW_WINSIZE_HEIGHT 600

void key_callback(GLFWwindow* window, int key, int scancode, int action,int mode);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    glfwInit();
    
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2);
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
    //    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    
    
    GLFWwindow *window = glfwCreateWindow(GLFW_WINSIZE_WIDTH,GLFW_WINSIZE_HEIGHT,"LearnOpenGL",nullptr,nullptr);
    
    if (window == nullptr)
    {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    //初始化opengl函数指针
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    int width, height;
    glfwGetFramebufferSize(window,&width,&height);
    glViewport(0,0,width,height);
    
    //================== 处理shader ======================
    
    const GLchar* verticesShaderSrc =
    "attribute vec4 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x,position.y,position.z,1.0);\n"
    "}";
    
    const GLchar* fragmentShaderSrc =
    "void main()\n"
    "{\n"
    "gl_FragColor = vec4(1.0,0.5,0.2,1.0);\n"
    "}\n";
    
    
    std::cout << verticesShaderSrc << std::endl;
    std::cout << fragmentShaderSrc << std::endl;
    
    GLuint verticesShader;
    verticesShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(verticesShader,1,&verticesShaderSrc,NULL);
    glCompileShader(verticesShader);
    
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(verticesShader,GL_COMPILE_STATUS,&success);
    
    if(!success)
    {
        glGetShaderInfoLog(verticesShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSrc,NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    GLuint shaderProgram;
    shaderProgram =  glCreateProgram();
    
    glAttachShader(shaderProgram,verticesShader);
    glAttachShader(shaderProgram,fragmentShader);
    
//    glUseProgram(shaderProgram);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    
    if(!success){
        
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        
    }
    
    
    glDeleteShader(verticesShader);
    glDeleteShader(fragmentShader);
    
    //=================== shader处理完成 =====================
    
    //================== 准备数据 ============================
    
    GLfloat vertices[]={
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f,
    };
    
    
    GLuint vao;
    
    
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,3 * sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindVertexArray(0);
    
    
    while(!glfwWindowShouldClose(window)){
        
        glfwPollEvents();
        //render
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES,0,3);
        
        glBindVertexArray(0);
        
        //end
        glfwSwapBuffers(window);
        
    }
    
    glfwTerminate();
    
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action , int mode){
    std::cout << "key" << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
