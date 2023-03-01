#include "message.h"

enum EntityType { BALL, PADDLE };

struct PositionMessage : public Message
{
    EntityType enityType;
    unsigned int positionX;
    unsigned int positionY;

    PositionMessage()
    {
        messageType = POSITION;
    }
};
