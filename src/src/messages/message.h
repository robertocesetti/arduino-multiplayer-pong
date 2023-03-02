#pragma once

enum MessageType {POSITION, POINT, SCENE};

struct Message
{
    MessageType messageType;
};