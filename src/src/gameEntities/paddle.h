#pragma once

#include "entity.h"
#include "collision.h"

class Paddle : public Entity
{
private:
    const unsigned int HEIGHT = 12;
    const unsigned int WIDTH = 2;
    unsigned int score = 0;

public:
    Paddle();
    ~Paddle();

    virtual Collision collideWithBoard(DisplayProperties* displayProperties);
    
    unsigned int getWidth() {return WIDTH;}
    unsigned int getHeight() {return HEIGHT;}
    unsigned int getScore() {return score;}
    void addPoint(){score+=1;}
    void resetScore(){score = 0;}

};