#ifndef CUBE_H
#define CUBE_H

#include "GameObject.h"
#include "Shader.h"
#include "Model.h"
#include "../include/glm/glm.hpp"
class ObjectCube : public GameObject {
    ObjectCube() {
        
    }

    void update() override {
        return;
    }

    void render() override {
        Shader* shader = model_->getShader();
        shader->setMat4("translation". translation_);
        shader->setMat4("view", game_->getCamera()->getView());
        shader->setMat4("projection", game_->getCamera()->getProjection());
        shader->setFloat("material.shininess", 64.0f);
        shader->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        shader->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        model_->render();
    }
};

#endif
