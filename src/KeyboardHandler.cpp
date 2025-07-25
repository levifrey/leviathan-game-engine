#include "KeyboardHandler.h"
#include <GLFW/glfw3.h>
void KeyboardHandler::handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keys_[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys_[key] = false;
    }
}

bool KeyboardHandler::getKeyDown(int key) {
    if (keys_.find(key) != keys_.end()) {
        return keys_[key];
    }
    return false;
}
