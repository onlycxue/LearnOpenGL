//
//  main.cpp
//  HelloShader
//
//  Created by playcrab on 16/10/14.
//  Copyright © 2016年 playcrab. All rights reserved.
//

#include <iostream>
#include <cmath>
#define GLEW_STATIC

#include "GL/glew.h"

#include "GLFW/glfw3.h"

#define GLFW_WINSIZE_WIDTH 800
#define GLFW_WINSIZE_HEIGHT 600

void key_callback(GLFWwindow* window, int key, int scancode, int action,int mode);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //fix glfwCreateWindow failed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 vertexColor;\n"
//    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x,position.y,position.z,1.0);\n"
    "vertexColor = color;\n"
    "}";
    
    const GLchar* fragmentShaderSrc =
    "#version 330 core\n"
    "out vec4 color;\n"
    "in vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "color = vec4(vertexColor,1.0f);\n"
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
    
//    GLfloat vertices[]={
//        //        -0.5f,-0.5f,0.0f,
//        //        0.5f,-0.5f,0.0f,
//        //        0.0f,0.5f,0.0f,
//        0.5f,0.5f,0.0f,
//        0.5f,-0.5f,0.0f,
//        -0.5f,-0.5f,0.0f,
//        -0.5f,0.5f,0.0f,
//    };
    
    GLfloat vertices[]={
        //位置          //颜色
        0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
        -0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
        0.0f, 0.5f,0.0f,  0.0f,0.0f,1.0f,
    };
    
    
//    GLuint indices[]={
//        0,1,3,
//        1,2,3
//    };
    
    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    //
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),(GLvoid*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    
//    GLuint ebo;
//    glGenBuffers(1,&ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    
    while(!glfwWindowShouldClose(window)){
        
        glfwPollEvents();
        //render
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
//        GLfloat time =  glfwGetTime();
//        GLfloat greenValue = sin(time) / 2 + 0.5;
//        
//        GLint vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
        //必须先UseProgram 才能 glUniform4f;
        glUseProgram(shaderProgram);
        
//        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
        
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES,0,3);
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,0);
        
        glBindVertexArray(0);
        
        //end
        glfwSwapBuffers(window);
        
    }
    const GLubyte* name = glGetString(GL_VERSION);
    
    std::cout << name << std::endl;
    
    glfwTerminate();
    
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action , int mode){
    std::cout << "key" << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

