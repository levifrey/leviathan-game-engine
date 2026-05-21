#include "Engine.h"
#include <glm/glm.hpp>

int main() {
    Game game(1000, 1000);

    PlayerCamera camera(&game);
    game.setCamera(camera.getComponent<Camera>());
    game.addGameObject(&camera);

    GameObject backpack(&game);

    ShaderID phongID = AssetManager::loadShader(
            PathUtils::shaderDir / "camera.vert",
            PathUtils::shaderDir / "flat.frag");

    ModelID backpackID = AssetManager::loadModel(PathUtils::objectDir / "backpack/backpack.obj");
    
    Transform* t = backpack.addComponent<Transform>();
    Renderer* r = backpack.addComponent<Renderer>(backpackID, phongID);
    t->translate(glm::vec3(5.0f, 1.0f, 1.0f));
    game.addGameObject(&backpack);

    game.Loop();
    
}
