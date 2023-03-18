#pragma once

#include "message.h"
#include "../scenes/scene.h"

struct ReadyMessage : public Message
{
    bool ready;

    ReadyMessage()
    {
        messageType = READY;
    }
};
