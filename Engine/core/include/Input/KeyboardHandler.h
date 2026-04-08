#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class KeyboardHandler {
    public:
        /*
         * Called each frame from GLFW through poll events
         */
        void handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

        /*
         * Request key state with GLFW keys consts: (GLFW_A, GLFW_B...)
         */
        bool getKeyDown(int key);
    private:
        std::map<int, bool> keys_;
};

#endif
