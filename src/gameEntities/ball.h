#pragma once

#include "entity.h"

class Ball : public Entity
{
private:
    const unsigned int RADIUS = 2;

public:
    Ball();
    ~Ball();

    unsigned int getRadius() { return RADIUS; }
    virtual bool Ball::collideWithBoard(DisplayProperties* displayProperties);
};