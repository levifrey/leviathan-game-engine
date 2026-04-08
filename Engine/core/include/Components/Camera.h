#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "Components/Component.h"

class Camera : public Component {
    public:
        Camera(float speed = 5.0f,
               float sensitivity = 0.15f,
               float fov = 45.0f,
               float aspect_ratio = 1.0f,
               float zNear = 0.1f,
               float zFar = 100.0f
               );
        void update() override;
        glm::mat4 getView();
        glm::mat4 getProjection();
        glm::vec3 getFront();
        glm::vec3 getPosition();
        void setSpeed(float speed) { speed_ = speed; }
        void setAspectRatio(float ratio) { aspect_ratio_ = ratio; }
        float getPitch() { return pitch_; }
        float getYaw() { return yaw_; }

    private:
        float fov_;
        float speed_;
        float sensitivity_;
        glm::vec3 up_;
        float yaw_ = 0;
        float pitch_ = 0;
        float aspect_ratio_;
        float zNear_;
        float zFar_;
};

#endif
