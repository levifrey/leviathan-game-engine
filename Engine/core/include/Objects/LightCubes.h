#pragma once
#include "GameObject.h"
#include "Components/AllComponents.h"
#include "glm/glm.hpp"
#include "AssetManager.h"

class AreaLightCube: public GameObject {
    public:
        explicit AreaLightCube(Game* game) : GameObject(game) {
            addComponent<Transform>();
            Model* model = AssetManager::getModel("default_box");
            Shader* shader = AssetManager::getShader("default_shader");
            addComponent<Renderer>(model, shader);
            addComponent<AreaLight>();
            game->addLightSource(getComponent<AreaLight>());
        }
};

class SpotLightCube: public GameObject {
    public:
        explicit SpotLightCube(Game* game) : GameObject(game) {
            addComponent<Transform>();
            Model* model = AssetManager::getModel("default_box");
            Shader* shader = AssetManager::getShader("default_shader");
            addComponent<Renderer>(model, shader);
            addComponent<SpotLight>(glm::vec3(1.0f, 0.0f, 0.0f), 12.5f, 17.5f);
            Transform* t = getComponent<Transform>();
            t->scale(glm::vec3(2.0f, 0.5f, 0.5f));
            game->addLightSource(getComponent<SpotLight>());
        }
};

class PointLightCube: public GameObject {
    public:
        explicit PointLightCube(Game* game) : GameObject(game) {
            addComponent<Transform>();
            Model* model = AssetManager::getModel("default_box");
            Shader* shader = AssetManager::getShader("default_shader");
            addComponent<Renderer>(model, shader);
            addComponent<PointLight>();
            game->addLightSource(getComponent<PointLight>());
        }
};

