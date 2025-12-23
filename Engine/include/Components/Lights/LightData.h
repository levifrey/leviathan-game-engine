#pragma once 
#include <glm/glm.hpp>

struct LightData {
    // Base class LightSource
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
    glm::vec3 position_;

    // PointLight
    float constant_;
    float linear_;
    float quadratic_;
    
    // DirectionalLight
    glm::vec3 direction_;

    // SpotLight
    float innerCutOff_;
    float outerCutOff_;
    
    int type;
};

enum LightType {
    AREA,
    POINT,
    DIRECTIONAL,
    SPOT
};
