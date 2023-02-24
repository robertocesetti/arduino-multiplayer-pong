#pragma once

#include "paddle.h"
#include "entity.h"

struct Boundary
{
    float x;
    float y;
    float width;
    float height;
};

class Ball : public Entity
{
private:
    const unsigned int RADIUS = 2;

    const float MIN_VELOCITY_X = 0.6f;
    const float MAX_VELOCITY_X = 1.2f;
    const float MAX_VELOCITY_Y = 3;

    void addRandomness(float randomX, float randomY);
    bool intersect(const Boundary &r1, const Boundary &r2);

public:
    Ball();
    ~Ball();

    unsigned int getRadius() { return RADIUS; }
    void collideWithPaddle(Paddle *paddle);
    virtual bool collideWithBoard(DisplayProperties *displayProperties);
};