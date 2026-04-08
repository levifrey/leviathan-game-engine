#define GLM_ENABLE_EXPERIMENTAL
#include "Components/Camera.h"
#include "Input/KeyboardHandler.h"
#include "Input/MouseHandler.h"
#include "DeltaClock.h"
#include "Game.h"
#include "Components/Transform.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera(
        float speed, 
        float sensitivity,
        float fov, 
        float aspect_ratio,
        float zNear,
        float zFar) {
    speed_ = speed;
    sensitivity_ = sensitivity;
    fov_ = fov;
    aspect_ratio_ = aspect_ratio;
    zNear_ = zNear;
    zFar_ = zFar;  
    up_ = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::update() {
    KeyboardHandler* kh = getGameObject()->getGame()->getKeyboardHandler();
    MouseHandler* mh = getGameObject()->getGame()->getMouseHandler();
    Transform* t = getGameObject()->getComponent<Transform>();

    yaw_ += mh->getMouseXOffset() * sensitivity_;
    pitch_ -= mh->getMouseYOffset() * sensitivity_;
    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = -89.0f;
    glm::quat rotation = 
        glm::angleAxis(glm::radians(yaw_), glm::vec3(0.0f, -1.0f, 0.0f)) * 
        glm::angleAxis(glm::radians(pitch_), glm::vec3(0.0f, 0.0f, 1.0f));
    t->setRotation(rotation);
    
    if (kh->getKeyDown(GLFW_KEY_W)) {
        t->translate(DeltaClock::getDeltaTime() * speed_ * getFront());
    }
    if (kh->getKeyDown(GLFW_KEY_S)) {
        t->translate(-DeltaClock::getDeltaTime() * speed_ * getFront());
    }
    if (kh->getKeyDown(GLFW_KEY_A)) {
        t->translate(-DeltaClock::getDeltaTime() * glm::normalize(glm::cross(getFront(), up_)) * speed_);
    }
    if(kh->getKeyDown(GLFW_KEY_D)) {
        t->translate(DeltaClock::getDeltaTime() * glm::normalize(glm::cross(getFront(), up_)) * speed_);
    }
}

glm::vec3 Camera::getFront() {
    return getGameObject()->getComponent<Transform>()->getRotation()  * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Camera::getPosition() {
    return getGameObject()->getComponent<Transform>()->getWorldPosition();
}

glm::mat4 Camera::getView() {
    return glm::lookAt(getPosition(), getPosition() + getFront(), up_);
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(glm::radians(fov_), aspect_ratio_, zNear_, zFar_);
}
