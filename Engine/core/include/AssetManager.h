#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;
class AssetManager {
public:
    static void init();
    static Model* getModel(const string& name);
    static Texture* getTexture(const string& name);
    static Shader* getShader( const string& name);

private:
    static unordered_map<string, Model> models_;
    static unordered_map<string, Texture> textures_;
    static unordered_map<string, Shader> shaders_;
};
