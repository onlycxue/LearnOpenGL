//
//  main.cpp
//  HelloWindow
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
    
    while(!glfwWindowShouldClose(window)){
        
        glfwPollEvents();
        //render
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
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
