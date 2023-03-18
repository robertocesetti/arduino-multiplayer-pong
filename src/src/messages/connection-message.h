#pragma once

#include "message.h"

struct ConnectionMessage : public Message 
{

    ConnectionMessage()
    {
        messageType = HANDSHAKE;
    }
};