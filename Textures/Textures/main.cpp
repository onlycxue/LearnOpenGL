//
//  main.cpp
//  Textures
//
//  Created by playcrab on 16/10/20.
//  Copyright © 2016年 playcrab. All rights reserved.
//

#include <iostream>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "SOIL/SOIL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


std::string resource_root = "/Users/playcrab/Documents/Project/GitProject/LearnOpenGL/Textures/Textures/res/";

void keyCallback(GLFWwindow*,int,int,int,int);

int main(int argc, const char * argv[]) {
    
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",nullptr,nullptr);
    
    if(window == nullptr)
    {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,keyCallback);
    
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK){
        std::cout << "failed to initialise GLEW" << std::endl;
    }
    
    //准备shader
    Shader* shader = new Shader(resource_root + "shader/normal.vsh",resource_root +"shader/normal.fsh");
    
    //准备顶点信息
    GLfloat vertices[]={
        //--位置---      --- 颜色 ---    -- 纹理坐标--
        0.5f,0.5f,0.0f,  1.0f,0.0f,0.0f,  1.0f,1.0f,    //右上
        0.5f,-0.5f,0.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,   //右下
        -0.5f,-0.5f,0.0f,  0.0f,0.0f,1.0f, 0.0f,0.0f,   //左下
        -0.5f,0.5f,0.0f,  1.0f,1.0f,0.0f,  0.0f,1.0f    //左上
        
    };
   
    GLint indexs[] = {0,1,3,1,2,3};
    
    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(6 * sizeof(GLfloat)));
    
    GLuint ebo;
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexs),indexs,GL_STATIC_DRAW);
    
//    glEnableVertexArrayAttrib(vbo,0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
    
    int width,height;
    
    GLuint texture1,texture2;
    glGenTextures(1, &texture1);
   
    
    //纹理1
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    unsigned char* image = SOIL_load_image((resource_root + "image/texture.jpg").c_str(),&width,&height,0,SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width,height, 0,GL_RGB, GL_UNSIGNED_BYTE,image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D,0);
    
    //纹理2
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    unsigned char* image2 = SOIL_load_image((resource_root + "image/awesomeface.png").c_str(), &width, &height,0,SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image2);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image2);
    glBindTexture(GL_TEXTURE_2D,0);
    
    while(!glfwWindowShouldClose(window)){
        
        glfwPollEvents();
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //render
        
       
        //glBindTexture(GL_TEXTURE_2D,texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1d(glGetUniformLocation(shader->getProgram(),"ourTexture1"),0); //0 对应着 texture0
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);
        glUniform1i(glGetUniformLocation(shader->getProgram(),"ourTexture2"),1); //1 对应着 texture1
        
         shader->use();
        glBindVertexArray(vao);
       
        glm::mat4 trans;
//        trans = glm::translate(trans,glm::vec3(0.5f,0.0f,-0.5f));
        trans = glm::rotate(trans,(GLfloat)glfwGetTime()* 10.0f,glm::vec3(0.0f,0.0f,1.0f));
        
        glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(),"transform"),1,GL_FALSE,glm::value_ptr(trans));
        
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        
        glBindVertexArray(0);
        //render end
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window ,int key,int scancode,int action,int mode){
    
    std::cout << "key" << std::endl;
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
}