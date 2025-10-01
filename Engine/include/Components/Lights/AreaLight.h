#ifndef AREALIGHT_H
#define AREALIGHT_H

#include <glm/glm.hpp>
#include <iostream>
#include "Components/LightSource.h"
#include "Components/Transform.h"

class AreaLight : public LightSource {
    public:
        AreaLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
            : LightSource(ambient, diffuse, specular) {}

        AreaLight() : LightSource() {}

        void applyUniforms(Shader* shader) override {
            LightSource::applyUniforms(shader);
            Transform* t = getGameObject()->getComponent<Transform>();
            if (!t) {
                std::cout << "ERROR>AreaLight>ApplyUniforms: No transform component found for parent game object." << std::endl;
            }
            shader->setVec3("light.position",  t->getWorldPosition());
        }
};

#endif
