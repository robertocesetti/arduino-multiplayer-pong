#pragma once

#include "entity.h"

class Paddle : public Entity
{
private:
    const unsigned int HEIGHT = 12;
    const unsigned int WIDTH = 2;

public:
    Paddle();
    ~Paddle();

    virtual bool collideWithBoard(DisplayProperties* displayProperties);
    
    unsigned int getWidth() {return WIDTH;}
    unsigned int getHeight() {return HEIGHT;}

};