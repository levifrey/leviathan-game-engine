#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "GameObject.h"
#include "Camera.h"
#include <vector>
class Game {
    public:
        Game(int window_width, int window_height);
        
        static void frameBufferSizeCallback(GLFWwindow* window, int width, int height); 
        static Game* GamePtr(GLFWwindow* window);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollCallback(GLFWwindow* window, double xpos, double ypos);

        MouseHandler* getMouseHandler();
        KeyboardHandler* getKeyboardHandler();
        Camera* getCamera();
        
        void Loop();
        void addGameObject(GameObject* obj);
    private:
        int window_width_;
        int window_height_;
        GLFWwindow* window_;
        Camera camera_;
        MouseHandler mouse_handler_;
        KeyboardHandler keyboard_handler_;
        std::vector<GameObject*> game_objects_;
};

#endif
