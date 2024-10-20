#pragma once
 
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "block.hh"
#include "object.hh"

class Game
{
private:
    int blockSize;
    Object* current;
    std::vector<std::vector<Block>> grid;
public:
    Game(/* args */);
    ~Game();
};