#pragma once 
#include "GameObject.h"
#include "AssetManager.h"
#include "Components/AllComponents.h"


class ContainerObject: public GameObject {
    public:
        explicit ContainerObject(Game* game) : GameObject(game) {
            addComponent<Transform>();
            Model* model = AssetManager::getModel("container");
            Shader* shader = AssetManager::getShader("light_shader");
            addComponent<Renderer>(model, shader);
        }
};
