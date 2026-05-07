#include "Components/Renderer.h"
#include "Components/Transform.h"
#include "GameObject.h"
#include "Game.h"
#include "Components/LightSource.h"

Renderer::Renderer(Model* model, Shader* shader) {
    model_ = model;
    shader_ = shader;
}

void Renderer::render() {
   effect_->render(model_, shader_, getGameObject());
}

/*
void Renderer::render() {
    shader_->use();
    GameObject* obj = getGameObject();
    if (obj->hasComponent<Transform>()) {
        shader_->setMat4("model", obj->getComponent<Transform>()->getWorldMatrix());
    }
    obj->getGame()->applyGlobalUniforms(shader_);
    shader_->setFloat("material.shininess", 10.0f);
    model_->draw(*shader_);
}
*/
