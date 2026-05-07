#include "AssetManager.h"
#include "Shapes.h"
#include "PathUtils.h"
#include "Mesh.h"
#include "Model.h"
namespace p = PathUtils;

std::unordered_map<std::string, Mesh> AssetManager::meshes_;

std::unordered_map<std::string, Texture> AssetManager::textures_;

std::unordered_map<std::string, Shader> AssetManager::shaders_;

std::unordered_map<std::string, Model> AssetManager::models_;

void AssetManager::init() {
    // --- Generated Meshes ---
    Mesh cube = createCube(1.0f);
    meshes_.emplace("cube", cube);

    Mesh plane = createFloor(1.0f);
    meshes_.emplace("plane", plane);
    
    // --- Textures ---
    unsigned char* black = new unsigned char[4]{0,0,0,255};
    Texture black_texture(black, 1, 1, TextureType::DEFAULT);
    Texture basic_container_diffuse(p::assetDir / "textures/container2.jpg", TextureType::DIFFUSE);
    Texture basic_container_specular(p::assetDir / "textures/container2_specular.jpg", TextureType::SPECULAR);
    Texture brick_diffuse(p::assetDir / "textures/brick.jpg", TextureType::DIFFUSE, true);
    Texture grass_diffuse(p::assetDir / "textures/grass.png", TextureType::DIFFUSE);
    textures_.emplace("black_texture", black_texture);
    textures_.emplace("basic_container_diffuse", basic_container_diffuse);
    textures_.emplace("basic_container_specular", basic_container_specular);
    textures_.emplace("brick_diffuse", brick_diffuse);
    textures_.emplace("grass_diffuse", grass_diffuse);
    
    // --- Shaders ---
    Shader default_shader(
            p::assetDir / "shaders/default.vert",
            p::assetDir / "shaders/default.frag");
    Shader light_shader(
            p::assetDir / "shaders/lights.vert",
            p::assetDir / "shaders/lights.frag");
    Shader flat_shader(
            p::assetDir / "shaders/flat.vert",
            p::assetDir / "shaders/flat.frag");
    Shader singleColor_shader(
            p::assetDir / "shaders/singleColor.vert",
            p::assetDir / "shaders/singleColor.frag");
    shaders_.emplace("default_shader", default_shader);
    shaders_.emplace("light_shader", light_shader);
    shaders_.emplace("flat_shader", flat_shader);
    shaders_.emplace("singleColor_shader", singleColor_shader);

    // --- Generated Models ---
    Model default_box = Model();
    default_box.addMesh(cube);
    models_.emplace("default_box", default_box);

    Model floor = Model();
    Mesh floor_plane = plane; 
    floor_plane.addTexture(brick_diffuse);
    floor.addMesh(floor_plane);
    models_.emplace("floor", floor);

    Model container = Model();
    Mesh container_cube = cube;
    container_cube.addTexture(basic_container_diffuse);
    container_cube.addTexture(basic_container_specular);
    container.addMesh(container_cube);
    models_.emplace("container", container);
    
    Model grass = Model();
    Mesh grass_plane = plane;
    grass_plane.addTexture(grass_diffuse);
    grass.addMesh(grass_plane);
    models_.emplace("grass", grass);
    
    // --- Models ---
    models_.try_emplace("backpack", Model(p::assetDir / "objects/backpack/backpack.obj", true));
    models_.try_emplace("cake", Model(p::assetDir / "objects/cake/Cake.obj"));
}

Mesh* AssetManager::getMesh(const string& name) {
    auto it = meshes_.find(name);
    if (it != meshes_.end()) {
        return &(it->second);
    }
    return nullptr;
}

Texture* AssetManager::getTexture(const string& name) {
    auto it = textures_.find(name);
    if (it != textures_.end()) {
        return &(it->second);
    }
    return nullptr;
}

Shader* AssetManager::getShader( const string& name) {
    auto it = shaders_.find(name);
    if (it != shaders_.end()) {
        return &(it->second);
    }
    return nullptr;
}

Model* AssetManager::getModel(const string& name) {
    auto it = models_.find(name);
    if (it != models_.end()) {
        return &(it->second);
    }
    return nullptr;

}
