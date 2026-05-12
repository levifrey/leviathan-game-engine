#include <glm/glm.hpp>
#include "Engine.h"
#include "Flashlight.h"

int main(int, char**) {
    Game game(1000, 1000);
    PlayerCamera camera(&game);
    game.addGameObject(&camera);
    game.setCamera(camera.getComponent<Camera>());

    AreaLightCube light1 = AreaLightCube(&game);
    AreaLightCube light2 = AreaLightCube(&game);

    Transform* t = light1.getComponent<Transform>();
    t->translate(glm::vec3(5.0f, 0.3f, 3.0f));
    t->scale(glm::vec3(0.5f, 0.5f, 0.5f));

    t = light2.getComponent<Transform>();
    t->translate(glm::vec3(5.0f, 0.3f, -3.0f));
    t->scale(glm::vec3(0.5f, 0.5f, 0.5f));

    SpotLightCube spotlight = SpotLightCube(&game);
    spotlight.addComponent<Flashlight>();
    camera.addChild(&spotlight);
    t = spotlight.getComponent<Transform>();
    t->translate(glm::vec3(1.5f, -0.5f, 0.5f));
    t->scale(glm::vec3(0.5f, 0.5f, 0.5f));

    ContainerObject box(&game);
    t = box.getComponent<Transform>();
    t->translate(glm::vec3(5.0f, 0.0f, 0.0f));

    game.addGameObject(&light1);
    game.addGameObject(&light2);
    game.addGameObject(&spotlight);
    game.addGameObject(&box);

    game.Loop();
}
