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

    unsigned int getPositionX() {return positionX;}
    unsigned int getPositionY(){return positionY;}
    unsigned int getWidth() {return WIDTH;}
    unsigned int getHeight() {return HEIGHT;}
};