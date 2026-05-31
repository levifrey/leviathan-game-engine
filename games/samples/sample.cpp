#include "Engine.h"
#include "../behaviors/Flashlight.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

/*
 * Sample Game Object Behaviors
 */
class OutlineBehavior : public Component {
    public:
    void init() override {
        Renderer* r = getGameObject()->getComponent<Renderer>();
        r->getOutlineConfig().color_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    void update() override {
        KeyboardHandler* k = getGameObject()->getGame()->getKeyboardHandler();
        if (k->getKeyDown(GLFW_KEY_O)) {
            outlined = !outlined;
            Renderer* r = getGameObject()->getComponent<Renderer>();
            if (outlined) {
                r->getOutlineConfig().active_ = true;
            } else {
                r->getOutlineConfig().active_ = false;
            }
        }
    }
    bool outlined = false;
};

class FlashLight : public Component {
    public:
    void init() override {
        SpotLight* sl = getGameObject()->getComponent<SpotLight>();
        sl->flipOnOff();
    }
    void update() override {
        KeyboardHandler* k = getGameObject()->getGame()->getKeyboardHandler();
        SpotLight* sl = getGameObject()->getComponent<SpotLight>();
        if (k->getKeyDown(GLFW_KEY_F)) {
            sl->flipOnOff();
        }
        Transform* t = getGameObject()->getComponent<Transform>();
        sl->setDirection(t->getWorldRotation() * glm::vec3(1.0f, 0.0f, 0.0f));
    }
    bool on_ = false;
};


int main() {
    /*
     * Game Intialization
     */
    Game game(1000, 1000);

    PlayerCamera camera(&game);
    game.setCamera(camera.getComponent<Camera>());
    game.addGameObject(&camera);

    /*
     * Load needed Assets
     */
    // Shaders
    ShaderID flatShader = AssetManager::loadShader(
            PathUtils::shaderDir / "camera.vert",
            PathUtils::shaderDir / "flat.frag");
    ShaderID phongShader = AssetManager::loadShader(
            PathUtils::shaderDir / "camera.vert",
            PathUtils::shaderDir / "lights.frag");
    ShaderID blurEffectShader = AssetManager::loadShader(
            PathUtils::shaderDir / "screen.vert",
            PathUtils::shaderDir / "blurScreen.frag");
    //game.setPostProcessingEffect(blurEffectShader);
    
    // Textures
    TextureID containerDiffuse = AssetManager::loadTexture(
            PathUtils::textureDir / "container2.jpg");
    TextureID containerSpecular = AssetManager::loadTexture(
            PathUtils::textureDir / "container2_specular.jpg");
    TextureID brickDiffuse = AssetManager::loadTexture(
            PathUtils::textureDir / "brick.jpg");

    std::filesystem::path cubeDir = PathUtils::textureDir / "skybox";
    TextureID skyCubemap = AssetManager::loadCubemap(
            {cubeDir / "right.jpg", cubeDir / "left.jpg", 
            cubeDir / "top.jpg", cubeDir / "bottom.jpg",
            cubeDir / "front.jpg", cubeDir / "back.jpg"});
    game.setSkybox(skyCubemap);
    
    // Materials
    MaterialID containerMaterial = AssetManager::storeMaterial({
            {{containerDiffuse, TextureType::DIFFUSE},
            {containerSpecular, TextureType::SPECULAR}}, 
            32.0f});
    MaterialID brickMaterial = AssetManager::storeMaterial({
            {{brickDiffuse, TextureType::DIFFUSE}},
            32.0f});

    // Meshes
    MeshID floorMesh = AssetManager::storeMesh(Shapes::createPlane(50.0f));

    // Models
    ModelID cakeModel = AssetManager::loadModel(PathUtils::objectDir / "cake/Cake.obj");
    ModelID backpackModel = AssetManager::loadModel(PathUtils::objectDir / "backpack/backpack.obj");
    ModelID containerModel = AssetManager::storeModel({{
            {AssetManager::defaultMeshes().cube_, containerMaterial}
            }});
    ModelID cubeModel = AssetManager::storeModel({{
            {AssetManager::defaultMeshes().cube_, AssetManager::defaultMaterials().textureless_}
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
    GameObject flashlight(&game);

    Transform* t;
    Renderer* r;
   
    /*
     * Describe Scene
     */

    // light cube
    t = lightCube.addComponent<Transform>();
    t->translate(glm::vec3(10.0f, -1.0f, 0.0f));
    r = lightCube.addComponent<Renderer>(cubeModel, AssetManager::defaultShaders().fallback_);
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
    container.addComponent<OutlineBehavior>();
    game.addGameObject(&container);

    // floor
    t = floor.addComponent<Transform>();
    r = floor.addComponent<Renderer>(floorModel, phongShader);
    t->translate(glm::vec3(01.0f, -3.0f, 0.0f));
    //game.addGameObject(&floor);

    // flashlight
    t = flashlight.addComponent<Transform>();
    SpotLight* s = flashlight.addComponent<SpotLight>();
    flashlight.addComponent<FlashLight>();
    camera.addChild(&flashlight);
    t->translate(glm::vec3(1.0f,-0.2f, 0.5f));
    game.addGameObject(&flashlight);
    game.addLightSource(s);

    game.Loop();
    
}
