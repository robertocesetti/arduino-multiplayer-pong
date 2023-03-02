#pragma once
#include "../display-properties.h"
#include "collision.h"
#include "../messages/position-message.h"

class Entity
{
protected:
    float positionX = 0.0f;
    float positionY = 0.0f;
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    unsigned int lastPositionX;
    unsigned int lastPositionY;

public:
    Entity();
    virtual ~Entity();

    void move();
    void updateVelocity(float vX, float vY);
    void reverseVelocityX();
    void reverseVelocityY();
    virtual Collision collideWithBoard(DisplayProperties* displayProperties) = 0;
    virtual bool preparePositionMessage(PositionMessage* positionMessage);
    
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
