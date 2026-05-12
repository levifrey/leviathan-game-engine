#pragma once
#include "RenderEffects/RenderEffect.h"
#include "Components/Transform.h"
#include "GameObject.h"
#include "Game.h"

class BasicEffect : public RenderEffect {
    void render(Model* model, Shader* shader, GameObject* obj) override {
        drawObject(model, shader, obj);
    }
};
