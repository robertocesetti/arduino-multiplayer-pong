#pragma once

#include "message.h"

struct PointMessage : public Message 
{
    short paddle1Point;
    short paddle2Point;

    PointMessage()
    {
        messageType = POINT;
    }
};