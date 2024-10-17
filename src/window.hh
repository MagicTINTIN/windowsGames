#pragma once
#define GLAD_GL_IMPLEMENTATION
#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <stdlib.h>
#include <stdio.h>

void error_callback(int error, const char* description);

class Window
{
private:
    GLFWwindow* window;
public:
    GLFWwindow* getWindow();
    Window();
    ~Window();
};