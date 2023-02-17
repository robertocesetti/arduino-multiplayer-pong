#pragma once

class Ball
{
private:
    unsigned int positionX = 0;
    unsigned int positionY = 0;
    int velocityX = 0;
    int velocityY = 0;
    const unsigned int RADIUS = 2;

public:
    Ball();
    ~Ball();
    void move();
    void updateVelocity(int vX, int vY);
    void reverseVelocityX();
    void reverseVelocityY();
    void setVelocityY(int velocityY) { this->velocityY = velocityY; }
    void setPosition(int positionX, int positionY);
    unsigned int getRadius() { return RADIUS; }
    unsigned int getPositionX() { return positionX; }
    unsigned int getPositionY() { return positionY; }
};