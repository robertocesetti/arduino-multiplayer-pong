#pragma once
#include "../display-properties.h"

class Entity
{
protected:
    float positionX = 0.0f;
    float positionY = 0.0f;
    float velocityX = 0.0f;
    float velocityY = 0.0f;

public:
    Entity();
    virtual ~Entity();

    void move();
    void updateVelocity(float vX, float vY);
    void reverseVelocityX();
    void reverseVelocityY();
    virtual bool collideWithBoard(DisplayProperties* displayProperties) = 0;
    
    void setPosition(float positionX, float positionY)
    {
        this->positionX = positionX;
        this->positionY = positionY;
    }
    void setVelocityY(float velocityY) { this->velocityY = velocityY; }

    unsigned int getPositionX() { return (unsigned int) positionX; }
    unsigned int getPositionY() { return (unsigned int) positionY; }
    float getVelocityX() { return velocityX; }
    float getVelocityY() { return velocityY; }
};
