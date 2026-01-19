#pragma once 
#include <glm/glm.hpp>

struct alignas(16) LightData {
    // Base class LightSource
    glm::vec4 position_type_;  // (x,y,z,type)
    glm::vec4 ambient_;   // (r,g,b)
    glm::vec4 diffuse_;   // (r,g,b)
    glm::vec4 specular_;  // (r,g,b)
    glm::vec4 direction_; // (x,y,z)
    glm::vec4 attenuation_; // (const, lin, quad)
    glm::vec4 spotlight_;   // (innerCutoff, outerCutoff) 
};

enum LightType {
    AREA,
    POINT,
    DIRECTIONAL,
    SPOT
};
