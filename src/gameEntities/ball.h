#pragma once

class Ball
{
private:
    unsigned int positionX = 0;
    unsigned int positionY = 0;
    int velocityX = 0;
    int velocityY = 0;
    const unsigned int RADIUS = 3;

public:
    Ball();
    ~Ball();
    void move();
    void updateVelocity(int vX, int vY);
    void reverseVelocityX();
    void reverseVelocityY();
    void setPosition(int positionX, int positionY);
    unsigned int getRadius();
    unsigned int getPositionX();
    unsigned int getPositionY();
};