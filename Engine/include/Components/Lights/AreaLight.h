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

        LightData packLightData() override {
            LightData data;
            data.ambient_ = ambient_;
            data.diffuse_ = diffuse_;
            data.specular_ = specular_;
            data.type = LightType::AREA;


            Transform* t = getGameObject()->getComponent<Transform>();
            if (!t) {
            } else {
                data.position_ = t->getWorldPosition();
            }

            return data;
        }
};

#endif
