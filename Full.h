#pragma once
#include "Obstacle.h"
class Full :
    public Obstacle
{
public:
    Full(String name, int x, int y);
    ~Full();

    virtual void restart();
};

