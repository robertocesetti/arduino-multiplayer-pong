typedef struct Ball {
    unsigned int positionX;
    unsigned int positionY;
    int velocityX;
    int velocityY;
    unsigned int RADIUS;
} Ball;

void move();
void updateVelocity(int vX, int vY);
void reverseVelocityX();
void reverseVelocityY();