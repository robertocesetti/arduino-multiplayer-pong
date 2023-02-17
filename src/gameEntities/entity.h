#pragma once

class Entity
{
protected:
    float positionX = 0;
    float positionY = 0;
    float velocityX = 0;
    float velocityY = 0;

public:
    Entity();
    ~Entity();

    void move();
    void updateVelocity(float vX, float vY);
    void reverseVelocityX();
    void reverseVelocityY();

    void setPosition(float positionX, float positionY)
    {
        this->positionX = positionX;
        this->positionY = positionY;
    }
    void setVelocityY(float velocityY) { this->velocityY = velocityY; }

    unsigned int getPositionX() { return (unsigned int) positionX; }
    unsigned int getPositionY() { return (unsigned int) positionY; }
};
