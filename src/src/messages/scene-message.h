#pragma once

#include "message.h"
#include "../scenes/scene.h"

struct SceneMessage : public Message
{
    SceneType sceneType;

    SceneMessage()
    {
        messageType = SCENE;
    }
};
