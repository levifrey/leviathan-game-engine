#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Game;
class Camera {
    public:
        Camera(Game* game = nullptr,
                glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
                float speed = 5.0f,
                float sensitivity = 0.25f,
                float fov = 45.0f,
                float yaw = 0.0f,
                float pitch = 0.0f,
                float aspect_ratio = 1.0f,
                float zNear = 0.1f,
                float zFar = 100.0f
                );
        void update();
        glm::mat4 getView();
        glm::mat4 getProjection();
        glm::vec3 getFront() { return front_; }
        glm::vec3 getPosition();
        void setSpeed(float speed) { speed_ = speed; }
        void setPosition(glm::vec3 pos) { pos_ = pos; }
        void setYaw(float yaw);
        void setPitch(float pitch);
        void setAspectRatio(float ratio) { aspect_ratio_ = ratio; }
    private:
        Game* game_;
        float fov_;
        float yaw_ = 0.0f;
        float pitch_= 0.0f;
        float speed_;
        float sensitivity_;
        glm::vec3 pos_;
        glm::vec3 front_;
        glm::vec3 up_;
        float aspect_ratio_;
        float zNear_;
        float zFar_;
};

#endif
