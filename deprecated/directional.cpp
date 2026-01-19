#include <glm/glm.hpp>
#include "Engine.h"
#include <vector>

int main(int, char**) {
    Game game(1000, 1000);
    
    Model cube = createCube(1.0f);
    
    // Shaders
    Shader directional_shader("../resources/shaders/directional.vert", "../resources/shaders/directional.frag");
    directional_shader.reserveTexture("material.diffuse", 0);
    directional_shader.reserveTexture("material.specular", 1);

    // Textures
    Texture diffuse("../resources/textures/container2.jpg");
    Texture specular("../resources/textures/container2_specular.jpg");

    // Game Object
    int num_cubes = 40;
    std::vector<GameObject> objects;
    objects.reserve(num_cubes);
    for (int i = 0; i < num_cubes; i++) {
        objects.emplace_back(&game);
        GameObject* obj = &objects[i];
        obj->addComponent<Transform>();
        obj->addComponent<Renderer>(&cube, &directional_shader);
        obj->getComponent<Renderer>()->addTexture(&diffuse, 0);
        obj->getComponent<Renderer>()->addTexture(&specular, 1);
        obj->getComponent<Transform>()->translate(glm::vec3(5.0f, 0.0f, -30 + i * 3.0f));
        obj->getComponent<Transform>()->rotate(0.3f * i, glm::vec3(0.0f, 0.0f, 1.0f)); 
        game.addGameObject(obj);
    }
    /*
    // obj1:
    std::vector<GameObject> objects;
    objects.emplace_back(&game);
    GameObject* obj1 = &objects[0];
    obj1->addComponent<Transform>();
    obj1->addComponent<Renderer>(&cube, &directional_shader);
    obj1->getComponent<Renderer>()->addTexture(&diffuse, 0);
    obj1->getComponent<Renderer>()->addTexture(&specular, 1);
    obj1->getComponent<Transform>()->translate(glm::vec3(5.0f, 0.0f, 0.0f));
    game.addGameObject(obj1);
    
    objects.emplace_back(&game);
    GameObject* obj2 = &objects[1];
    obj2->addComponent<Transform>();
    obj2->addComponent<Renderer>(&cube, &directional_shader);
    obj2->getComponent<Renderer>()->addTexture(&diffuse, 0);
    obj2->getComponent<Renderer>()->addTexture(&specular, 1);
    obj2->getComponent<Transform>()->translate(glm::vec3(5.0f, 0.0f, 0.0f));
    game.addGameObject(obj2);
    */

    
    // Light Object
    GameObject directional_light(&game);
    directional_light.addComponent<DirectionalLight>(glm::vec3(1.0f, -1.0f, 0.2f));
    game.addGameObject(&directional_light);
    game.setLightSource(directional_light.getComponent<DirectionalLight>());

    game.Loop();
}
