#include "Input/KeyboardHandler.h"
#include <GLFW/glfw3.h>
#include <iostream>


void KeyboardHandler::handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keys_[key].down_ = true;
        keys_[key].pressed_ = true;
    } else if (action == GLFW_RELEASE) {
        keys_[key].released_ = true;
        keys_[key].pressed_ = false;
    }
}

void KeyboardHandler::clearStates() {
    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        keys_[i].down_ = false;
        keys_[i].released_   = false;
    }
}
