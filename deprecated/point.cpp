#include <glm/glm.hpp>
#include "Engine.h"
#include <vector>

int main(int, char**) {
    Game game(1000, 1000);
    
    Model cube = createCube(1.0f);
    
    // Shaders
    Shader point_shader("../resources/shaders/light.vert", "../resources/shaders/point.frag");
    point_shader.reserveTexture("material.diffuse", 0);
    point_shader.reserveTexture("material.specular", 1);

    Shader default_shader("../resources/shaders/default.vert", "../resources/shaders/default.frag");

    // Textures
    Texture diffuse("../resources/textures/container2.jpg");
    Texture specular("../resources/textures/container2_specular.jpg");

    // Game Object
    int num_cubes = 20;
    std::vector<GameObject> objects;
    objects.reserve(num_cubes * num_cubes);
    for (int i = 0; i < num_cubes; i++) {
        for(int j = 0; j < num_cubes; j++) {
            objects.emplace_back(&game);
            GameObject* obj = &objects[i * num_cubes + j];
            obj->addComponent<Transform>();
            obj->addComponent<Renderer>(&cube, &point_shader);
            obj->getComponent<Renderer>()->addTexture(&diffuse, 0);
            obj->getComponent<Renderer>()->addTexture(&specular, 1);
            obj->getComponent<Transform>()->translate(glm::vec3(5.0f + i * 3.0f, -2.0f, -num_cubes * 3.0f / 2 + j * 3.0f));
            game.addGameObject(obj);
        }
    }
    
    // Light Object
    GameObject point_light(&game);
    point_light.addComponent<PointLight>();
    point_light.addComponent<Renderer>(&cube, &default_shader);
    point_light.addComponent<Transform>();
    point_light.getComponent<Transform>()->translate(glm::vec3(num_cubes * 3.0f / 2, 5.0f, 0.0f));
    game.addGameObject(&point_light);
    game.setLightSource(point_light.getComponent<PointLight>());

    game.Loop();
}
