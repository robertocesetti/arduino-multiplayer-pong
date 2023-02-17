#include "entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::move()
{
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