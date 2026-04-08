#include <glm/glm.hpp>
#include "Engine.h"
#include <vector>

int main(int, char**) {
    Game game(1000, 1000);
    PlayerCamera camera(&game);
    game.addGameObject(&camera);
    game.setCamera(camera.getComponent<Camera>());

    Model cube = createCube(1.0f);
    
    // Shaders
    Shader spot_shader("../resources/shaders/light.vert", "../resources/shaders/spot.frag");
    spot_shader.reserveTexture("material.diffuse", 0);
    spot_shader.reserveTexture("material.specular", 1);

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
            obj->addComponent<Renderer>(&cube, &spot_shader);
            obj->getComponent<Renderer>()->addTexture(&diffuse, 0);
            obj->getComponent<Renderer>()->addTexture(&specular, 1);
            obj->getComponent<Transform>()->translate(glm::vec3(5.0f + i * 3.0f, -2.0f, -num_cubes * 3.0f / 2 + j * 3.0f));
            game.addGameObject(obj);
        }
    }

    GameObject flashlight(&game);
    flashlight.addComponent<Transform>();
    flashlight.addComponent<SpotLight>();
    flashlight.addComponent<Flashlight>();
    flashlight.addComponent<Renderer>(&cube, &default_shader);
    camera.addChild(&flashlight);
    flashlight.getComponent<Transform>()->translate(glm::vec3(0.5f, -0.5f, 0.5f));
    flashlight.getComponent<Transform>()->scale(glm::vec3(3, 0.2f, 0.2f));
    game.setLightSource(flashlight.getComponent<SpotLight>());
    game.addGameObject(&flashlight);

    std::cout << "Loop Hit" << std::endl;
    game.Loop();
}
