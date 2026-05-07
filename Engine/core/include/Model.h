#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include <filesystem>
#include <Texture.h>
using namespace std;

class Model {
    public:
        Model(filesystem::path path, bool flipTextures = false) { 
            flipTextures_ = flipTextures;
            loadModel(path); 
        }
        Model() = default;
        void draw(Shader& shader);
        void addMesh(Mesh mesh);
    private:
        vector<Mesh> meshes_;
        filesystem::path directory_;
        bool flipTextures_;
        unordered_map<string, Texture> textures_loaded_;
        void loadModel(filesystem::path path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texType);
};
