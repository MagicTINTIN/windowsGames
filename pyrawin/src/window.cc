#include "window.hh"
#include <unistd.h>

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

Window::Window()
{
}


Window::Window(std::vector<Window> *otherWindows, int size, int screenW, int screenH, int speed, int ID)
    : movingRight(true), width(size), height(size), screenHeight(screenH), screenWidth(screenW), falling(false),
      posX((100 * rand()) % (screenW - size)), posY(0), speed(speed), otherWindows(otherWindows), ID(ID)
{
    window = glfwCreateWindow(width, height, "Box", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    int left, top, right, bottom;
    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
    frameWidth = right + left;
    if (top == 0)
        top = 15;
    frameHeight = bottom + top;
    printf("%d %d %d %d > [ID:%d] w:%d gwx:%d fh:%d\n", left, top, right, bottom, ID, width, getWX(), getYWithFrameHeight());

    // gladLoadGL();        // Load openGL function /!\ Can only be done AFTER making a valid window with an openGL context
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

int Window::getYWithFrameHeight()
{
    return posY - frameHeight;
}

int Window::getWX()
{
    return frameWidth + width;
}

int Window::getID()
{
    return ID;
}

bool Window::getFalling()
{
    return falling;
}

void Window::updatePos(int x, int y)
{
    posX = x;
    posY = y;
}

void Window::setFalling(bool v)
{
    falling = v;
}


void Window::fall()
{
    falling = true;
    int floor = screenHeight;
    for (Window &w : *otherWindows)
    {
        if (w.getID() == w.getID())
            continue;
        printf("\npx:%d wx:%d | [ID=%d] d: px:%d wx:%d > ", posX, width, w.getID(), w.getX(), w.getWX());
        if (posX + width <= w.getX() || posX >= w.getX() + w.getWX())
            continue;
        printf("floor:%d ny:%d nf:%d", floor, w.getYWithFrameHeight(), std::min(floor, w.getYWithFrameHeight()));
        floor = std::min(floor, w.getYWithFrameHeight());
    }
    printf("\n --- END ---\n");

    floor -= height;

    while (posY < floor)
    {
        posY += speed;
        if (posY >= floor)
            posY = floor;
        // printf("%d %d\n", posY, floor);
        glfwSetWindowPos(window, posX, posY);
        usleep(1000000 / 50);
        speed += 2;
    }
    falling = false;
}