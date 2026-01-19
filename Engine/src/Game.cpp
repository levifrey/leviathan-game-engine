#include "Game.h"
#include "Components/Renderer.h"
#include "GameObject.h"
#include <glad/glad.h>
#include "DeltaClock.h"
#include "Components/LightSource.h"
#include <iostream>
#include <glm/glm.hpp>

void printVectr(glm::vec3 vector) {
    std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;
}

void Game::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    GamePtr(window)->getCamera()->setAspectRatio((float)width/(float)height);
}

Game* Game::GamePtr(GLFWwindow* window) {
    return static_cast<Game*>(glfwGetWindowUserPointer(window));
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GamePtr(window)->getKeyboardHandler()->handleKeyPress(window, key, scancode, action, mods);
}

void Game::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    GamePtr(window)->getMouseHandler()->handleMouseMovement(window, xpos, ypos);
}

void Game::scrollCallback(GLFWwindow* window, double xpos, double ypos) {
    GamePtr(window)->getMouseHandler()->handleMouseScroll(window, xpos, ypos);
}

MouseHandler* Game::getMouseHandler() {
    return &mouse_handler_;
}

KeyboardHandler* Game::getKeyboardHandler() {
    return &keyboard_handler_;
}

Camera* Game::getCamera() {
    return camera_;
}

void Game::setCamera(Camera* camera) {
    camera_ = camera;
}

void Game::addGameObject(GameObject* obj) {
    game_objects_.push_back(obj);
}

void Game::addLightSource(LightSource* light) {
    light_sources_.push_back(light);
}

void Game::setDebugFunction(std::function<void(Game&)> debugFunction) {
    debugFunction_ = debugFunction;
}

/*
 * Creates OpenGL context and spawns window
 */
Game::Game(int window_width, int window_height) {

    // intialize window
    window_width_ = window_width;
    window_height_ = window_height;
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "ENGINE ERROR: with code: " << error << " and desc: " << description << std::endl;
    });

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    window_ = glfwCreateWindow(window_width_, window_height_, "GAME START", NULL, NULL); 
    if (window_ == NULL) {
        std::cout << "ENGINE ERROR: GLFW window failed to create!" << std::endl;
    } 
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ENGINE ERROR: Failed to intialize GLAD!" << std::endl;
    }   
    
    glViewport(0, 0, window_width_, window_height_);
    glEnable(GL_DEPTH_TEST);
    glClearColor(23.0f/255.0f, 19.0f/255.0f, 19.0f/255.0f, 1.0f);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // set callback functions
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, Game::frameBufferSizeCallback);
    glfwSetKeyCallback(window_, Game::keyCallback);
    glfwSetCursorPosCallback(window_, Game:: mouseMoveCallback);

    // Create important game objects:
    mouse_handler_ = MouseHandler();
    keyboard_handler_ = KeyboardHandler(); 

    // generate light UBO
    glGenBuffers(1, &lightUBO_);
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData) * MAX_LIGHTS + sizeof(int), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO_);

}

/*
 * Only called once after all objects have been generated
 */
void Game::Loop() {
    while(!glfwWindowShouldClose(window_)) {
        // check exit
        if (keyboard_handler_.getKeyDown(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window_, true);
        }

        // Graphics stuff
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mouse_handler_.update();  
        DeltaClock::tick();

        // Update and render objects
        for (GameObject* obj : game_objects_) {
            obj->update();
        }
        
        // send light data to GPU
        struct alignas(16) LightBlock {
            LightData light_data[MAX_LIGHTS];
            glm::vec4 lightCount;
        };
        struct LightBlock light_block;
        for (int i = 0; i < light_sources_.size(); i++) {
            light_block.light_data[i] = light_sources_[i]->packLightData();
        }
        light_block.lightCount[0] = light_sources_.size();

        glBindBuffer(GL_UNIFORM_BUFFER, lightUBO_);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightBlock), &light_block);
    
        for (GameObject* obj : game_objects_) {
            if(obj->hasComponent<Renderer>()) {
                Renderer* r = obj->getComponent<Renderer>();
                r->render();
            }
        }

        if (debugFunction_) {
            debugFunction_(*this);
        }
        
        // Update screen
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}



void Game::applyGlobalUniforms(Shader* shader) {
    shader->setMat4("view", getCamera()->getView());
    shader->setMat4("projection", getCamera()->getProjection());
    shader->setVec3("viewPos", getCamera()->getPosition());
}
