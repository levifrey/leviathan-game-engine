#include "GameObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"
GameObject::GameObject(Model* model, Shader* shader, Game* game) {
    model_ = model;
    game_ = game;
    shader_ = shader;
}

void GameObject::render() {
    shader_->use();
    for (int i = 0; i < textures_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[i]->getID());
    }
    model_->draw();
}

void GameObject::translate(glm::vec3 translation) {
    translation_ = glm::translate(translation_, translation);
}

void GameObject::rotate(float radians, glm::vec3 axis) {
    translation_ = glm::rotate(translation_, glm::radians(radians), axis);
}

void GameObject::scale(glm::vec3 factor) {
    translation_ = glm::scale(translation_, factor);
}

Shader* GameObject::getShader() { return shader_; }

Game* GameObject::getGame() { return game_; }

glm::mat4 GameObject::getTranslation() { return translation_; }

void GameObject::addTexture(Texture* texture, int index) {
    textures_.insert(textures_.begin() + index, texture);
}
