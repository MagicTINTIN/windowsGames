#include "window.hh"
 
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

Window::Window()
{
    window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }
 
    glfwMakeContextCurrent(window);
    gladLoadGL();//Load openGL function /!\ Can only be done AFTER making a valid window with an openGL context
    glfwSwapInterval(1); //Vsynch
}

Window::~Window()
{
}

GLFWwindow* Window::getWindow() {
    return this->window;
}