#include "Engine.h"
#include <glm/glm.hpp>

int main() {
    Game game(1000, 1000);

    PlayerCamera camera(&game);
    game.setCamera(camera.getComponent<Camera>());
    game.addGameObject(&camera);

    // Shaders
    ShaderID flatShader = AssetManager::loadShader(
            PathUtils::shaderDir / "camera.vert",
            PathUtils::shaderDir / "flat.frag");
    ShaderID phongShader = AssetManager::loadShader(
            PathUtils::shaderDir / "camera.vert",
            PathUtils::shaderDir / "lights.frag");
    
    // Textures
    TextureID containerDiffuse = AssetManager::loadTexture(
            PathUtils::textureDir / "container2.jpg");
    TextureID containerSpecular = AssetManager::loadTexture(
            PathUtils::textureDir / "container2_specular.jpg");
    TextureID brickDiffuse = AssetManager::loadTexture(
            PathUtils::textureDir / "brick.jpg");
    
    // Materials
    MaterialID containerMaterial = AssetManager::storeMaterial({
            {{containerDiffuse, TextureType::DIFFUSE},
            {containerSpecular, TextureType::SPECULAR}}, 
            32.0f});
    MaterialID brickMaterial = AssetManager::storeMaterial({
            {{brickDiffuse, TextureType::DIFFUSE}},
            32.0f });

    // Meshes
    MeshID floorMesh = AssetManager::storeMesh(Shapes::createPlane(50.0f));

    // Models
    ModelID cakeModel = AssetManager::loadModel(PathUtils::objectDir / "cake/Cake.obj");
    ModelID backpackModel = AssetManager::loadModel(PathUtils::objectDir / "backpack/backpack.obj");
    ModelID containerModel = AssetManager::storeModel({{
            {AssetManager::getGeometry().cube_, containerMaterial}
            }});
    ModelID cubeModel = AssetManager::storeModel({{
            {AssetManager::getGeometry().cube_, AssetManager::getMaterials().textureless_}
            }});
    ModelID floorModel = AssetManager::storeModel({{
            {floorMesh, brickMaterial}
            }});
    
    // Game Objects
    GameObject lightCube(&game);
    GameObject backpack(&game);
    GameObject container(&game);
    GameObject cake(&game);
    GameObject floor(&game);

    Transform* t;
    Renderer* r;
    
    // light cube
    t = lightCube.addComponent<Transform>();
    t->translate(glm::vec3(10.0f, -1.0f, 0.0f));
    r = lightCube.addComponent<Renderer>(cubeModel, AssetManager::getShaders().fallback_);
    AreaLight* l = lightCube.addComponent<AreaLight>();
    game.addGameObject(&lightCube);
    game.addLightSource(l);

    // backpack
    t = backpack.addComponent<Transform>();
    r = backpack.addComponent<Renderer>(backpackModel, phongShader);
    t->translate(glm::vec3(10.0f, -1.0f, -5.0f));
    game.addGameObject(&backpack);

    // container
    t = container.addComponent<Transform>();
    r = container.addComponent<Renderer>(containerModel, phongShader);
    t->translate(glm::vec3(10.0f, -1.0f, 5.0f));
    t->scale(glm::vec3(4.0f, 4.0f, 4.0f));
    game.addGameObject(&container);

    // floor
    t = floor.addComponent<Transform>();
    r = floor.addComponent<Renderer>(floorModel, phongShader);
    t->translate(glm::vec3(0.0f, -3.0f, 0.0f));
    game.addGameObject(&floor);

    game.Loop();
    
}
