#pragma once
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Components/lights/SpotLight.h"
/*
 * Component that dynamically rotates SpotLight based on Transform
 * REQUIRES: SpotLight, Transform
 */
class Flashlight : public Component {
    void update() override {
        Transform* t = getGameObject()->getComponent<Transform>();
        SpotLight* sl = getGameObject()->getComponent<SpotLight>();
        sl->setDirection(glm::normalize(glm::mat3(t->getWorldMatrix()) * glm::vec3(1.0f, 0.0f, 0.0f)));
    }
};

