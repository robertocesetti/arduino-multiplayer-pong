#pragma once

enum MessageType {POSITION, POINT, SCENE, READY, HANDSHAKE};

struct Message
{
    MessageType messageType;
};