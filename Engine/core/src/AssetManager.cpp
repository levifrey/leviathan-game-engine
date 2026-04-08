#include "AssetManager.h"
#include "Shapes.h"
#include "PathUtils.h"
namespace p = PathUtils;

std::unordered_map<std::string, Model> AssetManager::models_;

std::unordered_map<std::string, Texture> AssetManager::textures_;

std::unordered_map<std::string, Shader> AssetManager::shaders_;

void AssetManager::init() {
    // Models
    Model cube = createCube(1.0f);
    models_.emplace("cube", cube);

    // Textures
    Texture basic_container_diffuse(p::assetDir / "textures/container2.jpg");
    Texture basic_container_specular(p::assetDir / "textures/container2_specular.jpg");
    textures_.emplace("basic_container_diffuse", basic_container_diffuse);
    textures_.emplace("basic_container_specular", basic_container_specular);
    
    // Shaders
    Shader default_shader(
            p::assetDir / "shaders/default.vert",
            p::assetDir / "shaders/default.frag");
    Shader light_shader(
            p::assetDir / "shaders/lights.vert",
            p::assetDir / "shaders/lights.frag");
    light_shader.reserveTexture("material.diffuse", 0);
    light_shader.reserveTexture("material.specular", 1);
    shaders_.emplace("default_shader", default_shader);
    shaders_.emplace("light_shader", light_shader);
}

Model* AssetManager::getModel(const string& name) {
    auto it = models_.find(name);
    if (it != models_.end()) {
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
