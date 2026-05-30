#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input/MouseHandler.h"
#include "Input/KeyboardHandler.h"
#include "GameObject.h"
#include "Components/Camera.h"
#include "Shader.h"
#include "Components/LightSource.h"
#include <vector>
#include <functional>
#include "LightData.h"
#include "Texture.h"
#include "Model.h"

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
        void setCamera(Camera* camera);
        Camera* getCamera();
        void setDebugFunction(std::function<void(Game&)> debugFunction);
        
        void Loop();
        void addGameObject(GameObject* obj);
        void addLightSource(LightSource* light);
        void applyGlobalUniforms(const Shader& shader);
    private:
        int window_width_;
        int window_height_;
        GLFWwindow* window_;
        Camera* camera_;
        MouseHandler mouse_handler_;
        KeyboardHandler keyboard_handler_;
        std::vector<GameObject*> game_objects_;
        std::vector<LightSource*> light_sources_;
        GLuint lightUBO_;
        std::function<void(Game&)> debugFunction_;
        
        // used for frame buffering
        unsigned int frame_buffer_;
        unsigned int rbo_;
        unsigned int buffer_texture_;
};

#endif
