#ifndef LIGHTBEHAVIOR_H
#define LIGHTBEHAVIOR_H
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine.h"
class LightBehavior : public Component {
    public:

    void init() override {
        Transform* t = getGameObject()->getComponent<Transform>();
        t->translate(start_pos);
        t->translate(glm::vec3(radius, 0.0f, 0.0f));
    }

    void update() override {
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(100.0f) * DeltaClock::getDeltaTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 old_pos = getGameObject()->getComponent<Transform>()->getPosition() - start_pos;
        glm::vec3 new_pos = rot * glm::vec4(old_pos,1.0f);
        getGameObject()->getComponent<Transform>()->translate(new_pos-old_pos);
    }

    private:
        glm::vec3 start_pos{0.0f, 0.0f, 5.0f};
        float radius = 3.0f;
};

#endif
