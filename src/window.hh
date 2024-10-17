#pragma once
#define GLAD_GL_IMPLEMENTATION
#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <stdlib.h>
#include <stdio.h>
#include <vector>

void error_callback(int error, const char* description);

class Window
{
private:
    GLFWwindow* window;
    int height, width, posX, posY, screenWidth, screenHeight, speed;
    bool movingRight;
    std::vector<Window> otherWindows;
public:
    GLFWwindow* getWindow();
    Window();
    Window(std::vector<Window> &otherWindows, int size, int screenW, int screenH, int speed);
    ~Window();
    void horizontalMove();
    void fall();
    int getX();
    int getY();
    int getWX();
};