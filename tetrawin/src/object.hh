#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "block.hh"


class Object
{
private:
    Block *blocks[4];
    int posX, posY;
    int shape, rotation;

public:
    Object(/* args */);
    ~Object();
};