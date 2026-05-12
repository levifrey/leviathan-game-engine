#include "Engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <random>


class behaviour : public Component {
    void update() override {
        Transform* t = getGameObject()->getComponent<Transform>();
        t->rotate(1 * DeltaClock::getDeltaTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    }
};

int main(int, char**) {
    Game game(1000, 1000);
    
    // init camera
    PlayerCamera camera(&game);
    game.setCamera(camera.getComponent<Camera>());
    game.addGameObject(&camera);

    // init default model/shader
    Model* model = AssetManager::getModel("floor");
    Shader* shader = AssetManager::getShader("light_shader");
    
    // create the floor
    GameObject obj = GameObject(&game);
    obj.addComponent<Renderer>(model, shader);
    Transform* t = obj.addComponent<Transform>();
    t->translate(glm::vec3(0.0f, -5.0f, 0.0f));
    t->scale(glm::vec3(30.0f, 1.0, 30.0f));
    game.addGameObject(&obj);

    // create cake object
    GameObject cake(&game);
    Renderer* r = cake.addComponent<Renderer>(AssetManager::getModel("cake"), shader);
    r->setRenderEffect<OutlineEffect>(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), 0.01f);
    cake.addComponent<Transform>();
    cake.addComponent<behaviour>();
    t = cake.getComponent<Transform>();
    t->translate(glm::vec3(5.0f, -4.0f, 0.0f));
    t->scale(glm::vec3(0.05f, 0.05f, 0.05f));
    game.addGameObject(&cake);
    
    //init lights
    AreaLightCube light(&game);
    t = light.getComponent<Transform>();
    t->translate(glm::vec3(5.0f, 0.5f, 5.0f));
    r = light.getComponent<Renderer>();
    r->setRenderEffect<OutlineEffect>(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), 0.05f);
    game.addGameObject(&light);

    //grass
    int width = 15;
    shader = AssetManager::getShader("flat_shader");
    vector<GameObject> grass_vec;
    grass_vec.reserve(width*width);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            grass_vec.emplace_back(&game);
            GameObject& grass = grass_vec.back();
            grass.addComponent<Renderer>(AssetManager::getModel("window"), shader);
            t = grass.addComponent<Transform>();
            t->translate(glm::vec3(30/width*i-15, -3.5f, 30/width*j-15));
            t->rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            t->rotate(glm::radians((float)(rand() % 180)), glm::vec3(0.0f, 1.0f, 0.0f));
            t->scale(glm::vec3(3.0f, 1.0f, 3.0f));
            game.addGameObject(&grass);
        }
    }

    game.Loop();
}
