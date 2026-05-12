#include "Engine.h"
#include <cmath>
#include <iostream>

// a basic program to be used by a game object later
class lightBehavior : public Component {
    public: 
    void init() override {
        PointLight* p = getGameObject()->getComponent<PointLight>();
        p->setDiffuse(glm::vec3(1.0f, 0.0f, 0.0f));
    }
    
    void update() override {
        PointLight* p = getGameObject()->getComponent<PointLight>();
        time += DeltaClock::getDeltaTime();
        float white = 0.5f + 0.5f * std::sin(time);
        glm::vec3 diff = p->getDiffuse();
        diff.y = white;
        diff.z = white;
        p->setDiffuse(diff);
    }
    float time = 0.0f;
};

// Gives the object the highlight effect when "O" is pressed on the keyboard
class cakeBehavior : public Component {
    public:
    void update() override {
        KeyboardHandler* k = getGameObject()->getGame()->getKeyboardHandler();
        if (k->getKeyDown(GLFW_KEY_O)) {
            outlined = !outlined;
            Renderer* r = getGameObject()->getComponent<Renderer>();
            if (outlined) {
                r->setRenderEffect<BasicEffect>();
            } else {
                r->setRenderEffect<OutlineEffect>(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.03f);
            }
        }
    }
    bool outlined = false;
};

int main() {
    Game game(1000, 1000);

    // -- Make the camera --
    // Camera is controllable with WASD and mouse
    PlayerCamera camera(&game);
    game.setCamera(camera.getComponent<Camera>()); // lets the game access camera variable important for shading
    game.addGameObject(&camera); // allows the game to update the cameras component each frame
                                 
    Shader* shader = AssetManager::getShader("light_shader"); // set default shader

    //  -- Generate Game Objects --
    //  all game objects use the AssetManager which has some initlized models, textures and shaders
    
    GameObject floor(&game);
    GameObject cake(&game);
    
    // -- add floor attributes -- 

    // create plane model
    Mesh plane = Shapes::createPlane(100.0f); 
    plane.addTexture(*AssetManager::getTexture("brick_diffuse"));
    Model floor_model;
    floor_model.addMesh(plane);

    // add Object Components
    Renderer* r = floor.addComponent<Renderer>(&floor_model, shader);
    Transform* t = floor.addComponent<Transform>();

    // move floor down
    t->translate(glm::vec3(0.0f, -5.0f, 0.0f));
    game.addGameObject(&floor);

    // -- Make cake Game Object usind model generated from Assimp --
    r = cake.addComponent<Renderer>(AssetManager::getModel("cake"), shader);
    t = cake.addComponent<Transform>();
    t->translate(glm::vec3(5.0f, -5.0f, 0.0f));
    t->scale(glm::vec3(0.05f, 0.05f, 0.05f)); // it's very big so we need to scale it down
    cake.addComponent<cakeBehavior>(); // give it the highlight behavior
    game.addGameObject(&cake);

    // -- Create a light cube object already implemented from the Engine --
    PointLightCube light(&game);
    light.getComponent<Transform>()->translate(glm::vec3(5.0f, 2.0f, 0.0f));
    game.addGameObject(&light);
    light.addComponent<lightBehavior>(); // attach a custom behavior to the object

    // start game 
    game.Loop();
}
