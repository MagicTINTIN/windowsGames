#include "window.hh"
#include <unistd.h>

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

Window::Window() {

}

Window::Window(std::vector<Window> &otherWindows, int size, int screenW, int screenH, int speed)
    : movingRight(true), width(size), height(size), screenHeight(screenH), screenWidth(screenW),
      posX((100 * rand()) % (screenW - size)), posY(0), speed(speed), otherWindows(otherWindows)
{
    window = glfwCreateWindow(width, height, "Box", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();        // Load openGL function /!\ Can only be done AFTER making a valid window with an openGL context
    glfwSwapInterval(1); // Vsynch
}

Window::~Window()
{
}

GLFWwindow *Window::getWindow()
{
    return this->window;
}

void Window::horizontalMove()
{
    // int x, y;
    // glfwGetWindowPos(window, &x, &y);
    if (posX + width >= screenWidth)
        movingRight = false;
    if (posX <= 0)
        movingRight = true;

    if (movingRight)
        posX += speed;
    else
        posX -= speed;

    glfwSetWindowPos(window, posX, posY);
    // posX = x;
    // posY = y;
}

int Window::getX()
{
    return posX;
}

int Window::getY()
{
    return posY;
}

int Window::getWX()
{
    return width;
}

void Window::fall()
{
    int floor = screenHeight;
    for (Window &w : otherWindows)
    {
        if (posX + width <= w.getX() || posX >= w.getX() + w.getWX())
            continue;
        floor = std::min(floor, w.getY());
    }

    floor -= height;

    while (posY < floor)
    {
        posY+=speed;
        // printf("%d %d\n", posY, floor);
        glfwSetWindowPos(window, posX, posY);
        usleep(1000000 / 50);
    }
}