#pragma once

#include "entity.h"
#include "ball.h"

class Paddle : public Entity
{
private:
    const unsigned int HEIGHT = 12;
    const unsigned int WIDTH = 2;

public:
    Paddle();
    ~Paddle();

    virtual bool Paddle::collideWithBoard(DisplayProperties* displayProperties);
    
    void moveUsingAI(Ball* ball, bool godMode = false);

    unsigned int getWidth() {return WIDTH;}
    unsigned int getHeight() {return HEIGHT;}

};