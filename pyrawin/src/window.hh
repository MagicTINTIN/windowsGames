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
    int ID, height, width, posX, posY, screenWidth, screenHeight, speed;
    int frameHeight, frameWidth;
    bool movingRight;
    std::vector<Window> *otherWindows;
    bool falling;
    void setFalling(bool v);
public:
    GLFWwindow* getWindow();
    Window();
    Window(std::vector<Window> *otherWindows, int size, int screenW, int screenH, int speed, int ID);
    ~Window();
    void horizontalMove();
    void fall();
    int getX();
    int getY();
    int getYWithFrameHeight();
    int getWX();
    int getID();
    bool getFalling();
    void updatePos(int x, int y);
};