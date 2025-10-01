#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <glm/glm.hpp>
#include "Components/LightSource.h"
#include "Shader.h"
#include "Components/Transform.h"

class SpotLight : public LightSource {
    public:
        SpotLight(glm::vec3 direction, float innerCutoff, float outerCutoff,
            glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
            : LightSource (ambient, diffuse, specular) 
        {
            direction_ = direction;
            innerCutoff_ = innerCutoff;
            outerCutoff_ = outerCutoff;
        }


        SpotLight(glm::vec3 direction, float innerCutoff, float outerCutoff)
            : LightSource() 
        {
            direction_ = direction;
            innerCutoff_ = innerCutoff;
            outerCutoff_ = outerCutoff;
        }

        SpotLight() : LightSource() {
            direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
            innerCutoff_ = 12.5f;
            outerCutoff_ = 17.5f;
        }

        void applyUniforms(Shader* shader) override {
            LightSource::applyUniforms(shader);
            shader->setFloat("light.innerCutoff", glm::cos(glm::radians(innerCutoff_)));
            shader->setFloat("light.outerCutoff", glm::cos(glm::radians(outerCutoff_)));
            shader->setVec3("light.direction", direction_);
            Transform* t = getGameObject()->getComponent<Transform>();
            if(!t) {
                std::cout << "ERROR>SpotLight>applyUniforms: No transform component found for parent game object." << std::endl;
            }
            shader->setVec3("light.position", t->getWorldPosition());
        }

        glm::vec3 getDirection() { return direction_; }
        void setDirection(glm::vec3 direction) { direction_ = direction; }
        float getInnerCutoff() { return innerCutoff_; }
        float getOuterCutoff() { return outerCutoff_; }
        void setInnerCutoff(float cutoff) { innerCutoff_ = cutoff; }
        void setOuterCutoff(float cutoff) { outerCutoff_ = cutoff; }
    private:
        glm::vec3 direction_;
        float innerCutoff_;
        float outerCutoff_;
};

#endif
