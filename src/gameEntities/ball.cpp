#include "ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::move(){
    positionX += velocityX;
    positionY += velocityY;
}

void Ball::updateVelocity(int vX, int vY){
    velocityX = vX;
    velocityY = vY;
}

void Ball::reverseVelocityX(){
    velocityX = -velocityX;
}

void Ball::reverseVelocityY(){
    velocityY = -velocityY;
}

void Ball::setPosition(int positionX, int positionY){
    this->positionX = positionX; 
    this->positionY = positionY; 
}