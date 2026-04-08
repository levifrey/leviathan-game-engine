#include "Components/Renderer.h"
#include "Components/Transform.h"
#include "GameObject.h"
#include "Game.h"
#include "Components/LightSource.h"

Renderer::Renderer(Model* model, Shader* shader) {
    model_ = model;
    shader_ = shader;
}

void Renderer::addTexture(Texture* texture, int index) {
    textures_.insert(textures_.begin() + index, texture);
}

void Renderer::render() {
    shader_->use();
    GameObject* obj = getGameObject();
    if (obj->hasComponent<Transform>()) {
        shader_->setMat4("model", obj->getComponent<Transform>()->getWorldMatrix());
    }
    obj->getGame()->applyGlobalUniforms(shader_);
    for (int i = 0; i < textures_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[i]->getID());
    }
    shader_->setFloat("material.shininess", 10.0f);
    model_->draw();
}
