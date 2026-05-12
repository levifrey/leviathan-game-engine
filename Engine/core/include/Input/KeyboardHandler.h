#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

struct KeyState {
    bool down_;
    bool pressed_;
    bool released_;
};

class KeyboardHandler {
    public:
        KeyboardHandler() {
            for (int i = 0; i <= GLFW_KEY_LAST; i++) {
                keys_[i].down_     = false;
                keys_[i].released_ = false;
                keys_[i].pressed_  = false;
            }
        }
        /*
         * Called each frame from GLFW through poll events
         */
        void handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

        /*
         * Request key state with GLFW keys consts: (GLFW_A, GLFW_B...)
         */
        bool getKeyDown(int key) { return keys_[key].down_; }
        bool getKeyPressed(int key) { return keys_[key].pressed_; }
        bool getKeyReleased(int key) { return keys_[key].released_; }

        void clearStates();
    private:
        std::array<KeyState, GLFW_KEY_LAST+1> keys_;
};

#endif
