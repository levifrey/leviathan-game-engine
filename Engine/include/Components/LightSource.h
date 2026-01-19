#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/glm.hpp>
#include "Component.h"
#include "Shader.h"
#include "LightData.h"

class LightSource : public Component {
    public:
        LightSource(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
            ambient_ = ambient;
            diffuse_ = diffuse;
            specular_ = specular;
        }

        LightSource() {
            ambient_ = glm::vec3(0.3f, 0.3f, 0.3f);
            diffuse_ = glm::vec3(0.5f, 0.5f, 0.5f);
            specular_ = glm::vec3(1.0f, 1.0f, 1.0f);
        }

        virtual LightData packLightData();

        glm::vec3 getAmbient() { return ambient_; }
        glm::vec3 getDiffuse() { return diffuse_; }
        glm::vec3 getSpecular() { return specular_; }
    private:
        glm::vec3 ambient_;
        glm::vec3 diffuse_;
        glm::vec3 specular_;
};

#endif
