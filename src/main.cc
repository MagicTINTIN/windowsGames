#define GLAD_GL_IMPLEMENTATION
#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "window.hh"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        speed += 10;
        windows.push_back(currentWindow);
        currentWindow = Window(windows, 100, screenW, screenH, speed);
        window = currentWindow.getWindow();
    }
}

std::vector<Window> windows;
Window currentWindow;
GLFWwindow *window;
int screenW, screenH;
int speed;

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // get screen size
    int monitorsCount = 0;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorsCount);
    const GLFWvidmode *mode = glfwGetVideoMode(monitors[0]);

    screenH = mode->height;
    screenW = mode->width;

    speed = 10;

    currentWindow = Window(windows, 100, screenW, screenH, speed);
    window = currentWindow.getWindow();

    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram(program);
        // glBindVertexArray(vertex_array);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        currentWindow.horizontalMove();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}