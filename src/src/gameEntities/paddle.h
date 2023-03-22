#pragma once

#include "entity.h"
#include "collision.h"

#define MAX_SCORE 5

class Paddle : public Entity
{
private:
    const unsigned int HEIGHT = 12;
    const unsigned int WIDTH = 2;
    unsigned int score = 0;
    unsigned int lastScore = 0;

public:
    Paddle();
    ~Paddle();

    virtual Collision collideWithBoard(DisplayProperties* displayProperties);
    bool preparePositionMessage(PositionMessage* positionMessage) override;
    void addPoint();
    
    unsigned int getWidth() {return WIDTH;}
    unsigned int getHeight() {return HEIGHT;}
    unsigned int getScore() {return score;}
    bool isScoreChanged() { return lastScore != score;}
    void setPoint(short point){score=point;}
    void resetScore();
    bool won() { return score >= MAX_SCORE; }

};