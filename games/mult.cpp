#include <glm/glm.hpp>
#include "Engine.h"

int main(int, char**) {
    Game game(1000, 1000);
    PlayerCamera camera(&game);
    game.addGameObject(&camera);
    game.setCamera(camera.getComponent<Camera>());

    Model cube = createCube(1.0f);
}
