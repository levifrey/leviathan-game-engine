#ifndef DIRECTIONAL_LIGHT_SOURCE_H
#define DIRECTIONAL_LIGHT_SOURCE_H

#include "Components/Component.h"
#include "Components/LightSource.h"

class DirectionalLight : public LightSource {
    public: 
        DirectionalLight(
                glm::vec3 direction,
                glm::vec3 ambient, 
                glm::vec3 diffuse, 
                glm::vec3 specular) 
            : LightSource(ambient, diffuse, specular) {
            direction_ = direction;
        }

        DirectionalLight() : LightSource() {
            direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
        }

        DirectionalLight(glm::vec3 direction) : LightSource() {
            direction_ = direction;
        }

        void applyUniforms(Shader* shader) override {
            LightSource::applyUniforms(shader);
            shader->setVec3("light.direction", direction_);
        }
    private:
        glm::vec3 direction_;
};

#endif
