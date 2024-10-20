#define GLAD_GL_IMPLEMENTATION
// #include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// #include "../includes/linmath.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int sizeX(256), sizeY(256);
int keys[348] = {0};

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    keys[key] = action == GLFW_PRESS ? 1 : 0;
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    printf("x:%f y:%f\n", xpos, ypos);
    // glfwSetWindowPos(window, (int)xpos, (int)ypos);
}

void window_focus_callback(GLFWwindow* window, int focused)
{
    if (focused == 0)
    {
        glfwFocusWindow(window);
    }
}

int findNewPos1D(int actualPos, int size, double cursorPos)
{
    int cursorIntPos = (int)cursorPos;
    if (cursorIntPos - size > 0)
    {
        return actualPos + (cursorIntPos - size);
    }
    else if (cursorPos < 0)
    {
        return actualPos + cursorIntPos;
    }
    else
        return actualPos;
}

int findNewSizeAndPos1D(int actualPos, int *size, double cursorPos)
{
    int cursorIntPos = (int)cursorPos;
    if (cursorIntPos - *size > 0)
    {
        *size = cursorIntPos;
        return actualPos;
    }
    else if (cursorPos < 0)
    {
        *size -= cursorIntPos;
        return actualPos + cursorIntPos;
    }
    else
        return actualPos;
}

void adjustPosition(GLFWwindow *window)
{
    double mouse_x, mouse_y;
    int window_x, window_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    glfwGetWindowPos(window, &window_x, &window_y);
    printf("Mouse: X:%f Y:%f - Window: X:%d Y:%d\n", mouse_x, mouse_y, window_x, window_y);
    // glfwSetWindowPos(window, (int)mouse_x, (int)mouse_y);
    glfwSetWindowPos(window, findNewPos1D(window_x, sizeX, mouse_x), findNewPos1D(window_y, sizeY, mouse_y));
}

void adjustSize(GLFWwindow *window)
{
    double mouse_x, mouse_y;
    int window_x, window_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    glfwGetWindowPos(window, &window_x, &window_y);
    printf("Mouse: X:%f Y:%f - Window: X:%d Y:%d\n", mouse_x, mouse_y, window_x, window_y);
    // glfwSetWindowPos(window, (int)mouse_x, (int)mouse_y);
    glfwSetWindowPos(window, findNewSizeAndPos1D(window_x, &sizeX, mouse_x), findNewSizeAndPos1D(window_y, &sizeY, mouse_y));
    glfwSetWindowSize(window, sizeX, sizeY);
}

int main(int argc, char const *argv[])
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(sizeX, sizeY, "Stupid Window", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);

    glfwMakeContextCurrent(window);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        if (keys[GLFW_KEY_LEFT_SHIFT])
            adjustSize(window);
        else
            adjustPosition(window);

        glfwFocusWindow(window);
        glfwShowWindow(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}