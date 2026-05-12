#pragma once
#include <string>
#include <unordered_map>
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"

using namespace std;
class AssetManager {
public:
    static void init();
    static Mesh*    getMesh(const string& name);
    static Texture* getTexture(const string& name);
    static Shader*  getShader(const string& name);
    static Model*   getModel(const string& name);
private:
    static unordered_map<string, Mesh> meshes_;
    static unordered_map<string, Texture> textures_;
    static unordered_map<string, Shader> shaders_;
    static unordered_map<string, Model> models_;
};
