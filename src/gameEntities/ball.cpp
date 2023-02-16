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
    positionX = -positionX;
}

void Ball::reverseVelocityY(){
    positionY = -positionY;
}

void Ball::setPosition(int positionX, int positionY){
    this->positionX = positionX; 
    this->positionY = positionY; 
}

unsigned int Ball::getRadius(){
    return RADIUS;
}

unsigned int Ball::getPositionX(){
    return positionX;
}

unsigned int Ball::getPositionY(){
    return positionY;
}