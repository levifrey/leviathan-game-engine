#include "Camera.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "DeltaClock.h"
#include "Game.h"
#include <cmath>
#include <GLFW/glfw3.h>

glm::vec3 getDirectionVector(float yaw, float pitch) {
    glm::vec3 directionVec;
    directionVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    directionVec.y = sin(glm::radians(pitch));
    directionVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(directionVec);
}


Camera::Camera(
        Game* game,
        glm::vec3 position,  
        float speed, 
        float sensitivity,
        float fov, 
        float yaw, 
        float pitch,
        float aspect_ratio,
        float zNear,
        float zFar) {
    game_ = game;
    pos_ = position;
    speed_ = speed;
    sensitivity_ = sensitivity;
    fov_ = fov;
    aspect_ratio_ = aspect_ratio;
    zNear_ = zNear;
    zFar_ = zFar; 
    yaw_ = yaw;
    pitch_= pitch;
    front_ = getDirectionVector(yaw_, pitch_);
    up_ = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::update() {
    yaw_ += game_->getMouseHandler()->getMouseXOffset() * sensitivity_;
    pitch_ -= game_->getMouseHandler()->getMouseYOffset() * sensitivity_;
    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = 89.0f;
    front_ = getDirectionVector(yaw_, pitch_);
    if (game_->getKeyboardHandler()->getKeyDown(GLFW_KEY_W)) {
        pos_ += DeltaClock::getDeltaTime() * speed_ * front_;
    }
    if (game_->getKeyboardHandler()->getKeyDown(GLFW_KEY_S)) {
        pos_ -= DeltaClock::getDeltaTime() * speed_ * front_;
    }
    if (game_->getKeyboardHandler()->getKeyDown(GLFW_KEY_A)) {
        pos_ -= DeltaClock::getDeltaTime() * glm::normalize(glm::cross(front_, up_)) * speed_;
    }
    if(game_->getKeyboardHandler()->getKeyDown(GLFW_KEY_D)) {
        pos_ += DeltaClock::getDeltaTime() * glm::normalize(glm::cross(front_, up_)) * speed_;
    }
}

glm::vec3 Camera::getPosition() {
    return pos_;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(pos_, pos_ + front_, up_);
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(glm::radians(fov_), aspect_ratio_, zNear_, zFar_);
}

void Camera::setYaw(float yaw) {
    yaw_ = yaw;
    front_ = getDirectionVector(yaw_, pitch_);
}

void Camera::setPitch(float pitch) {
    pitch_ = pitch;
    if (pitch_ > 89.0f) {
        pitch_ = 89.0f;
    }
    if (pitch_ -89.0f) {
        pitch_ = -89.0f;
    }
    front_ = getDirectionVector(yaw_, pitch_);
}   




