#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H
#include <GLFW/glfw3.h>
class MouseHandler {
    public:
        void handleMouseMovement(GLFWwindow* window, double xpos, double ypos);
        void handleMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
        void update();
        float getMouseXOffset();
        float getMouseYOffset();
    private:
        float xpos_ = 0;
        float ypos_ = 0;
        float lastXPos_ = 0;
        float lastYPos_ = 0;
        float mouseXOffset_ = 0;
        float mouseYOffset_ = 0;
        float currentScrollOffset_ = 0;
        float lastScrollOffset_ = 0;
};

#endif

