#pragma once 
#include "GameObject.h"
#include "AssetManager.h"
#include "Components/AllComponents.h"


class ContainerObject: public GameObject {
    public:
        explicit ContainerObject(Game* game) : GameObject(game) {
            addComponent<Transform>();
            Model* model = AssetManager::getModel("cube");
            Shader* shader = AssetManager::getShader("light_shader");
            addComponent<Renderer>(model, shader);
            getComponent<Renderer>()->addTexture(AssetManager::getTexture("basic_container_diffuse"), 0);
            getComponent<Renderer>()->addTexture(AssetManager::getTexture("basic_container_specular"), 1);
        }
};
