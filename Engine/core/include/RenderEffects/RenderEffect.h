#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Model.h"
#include "Components/Transform.h"
#include "Game.h"

class RenderEffect {
    public:
    virtual ~RenderEffect() = default;
    virtual void render(Model* model, Shader* shader, GameObject* obj) = 0;
    void drawObject(Model* model, Shader* shader, GameObject* obj) {
        shader->use();
        if (obj->hasComponent<Transform>()) {
            shader->setMat4("model", obj->getComponent<Transform>()->getWorldMatrix());
        }
        // what are the global uniforms
        obj->getGame()->applyGlobalUniforms(shader);
        // why is shininess important??
        shader->setFloat("material.shininess", 10.0f);
        // why does model need shader
        model->draw(*shader);
    }
};
