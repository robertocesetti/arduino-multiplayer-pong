#pragma once

class Paddle
{
private:
    unsigned int positionX = 10;
    unsigned int positionY = 0;
    int velocity = 0;
    const unsigned int HEIGHT = 10;
    const unsigned int WIDTH = 2;

public:
    Paddle();
    ~Paddle();
    void setPosition(int pX, int pY);
    int getWidth();
    int getHeight();
};