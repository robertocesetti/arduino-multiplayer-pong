#include "entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::move()
{
    lastPositionX = (unsigned int)positionX;
    lastPositionY = (unsigned int)positionY;

    positionX += velocityX;
    positionY += velocityY;
}

void Entity::updateVelocity(float vX, float vY)
{
    velocityX = vX;
    velocityY = vY;
}

void Entity::reverseVelocityX()
{
    velocityX = -velocityX;
}

void Entity::reverseVelocityY()
{
    velocityY = -velocityY;
}

bool Entity::preparePositionMessage(PositionMessage *positionMessage)
{
    if (lastPositionX == getPositionX() && lastPositionY == getPositionY())
        return false;

    positionMessage->positionX = getPositionX();
    positionMessage->positionY = getPositionY();
    return true;
}