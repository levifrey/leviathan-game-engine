#include "DeltaClock.h"

float DeltaClock::lastTime_ = 0.0;
float DeltaClock::deltaTime_ = 0.0;

void DeltaClock::tick() {
    deltaTime_ = glfwGetTime() - lastTime_;
    lastTime_ = glfwGetTime();
}

float DeltaClock::getDeltaTime() { return deltaTime_; }

