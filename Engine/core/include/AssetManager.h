#pragma once

// standard
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <functional>

// from Engine
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"
#include "AssetTypes.h"
#include "Material.h"

// Used for Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class AssetManager {

private:

    struct DefaultShaders {
        ShaderID outline_;
    };



public:
    static void init();

    static const Mesh& getMesh(MeshID id);
    static const Texture& getTexture(TextureID id);
    static const Material& getMaterial(MaterialID id);
    static const Model& getModel(ModelID id);
    static const Shader& getShader(ShaderID id);

    static ModelID loadModel(const std::filesystem::path& path);
    static TextureID loadTexture(const std::filesystem::path& path);
    static ShaderID loadShader(
            const std::filesystem::path& vertex_path, 
            const std::filesystem::path& fragment_path);

    static const DefaultShaders& getShaders() { return defaultShaders_; }


private:

    struct LoadContext {
        std::filesystem::path directory_;
        std::unordered_map<int, MaterialID> material_cache_;
        Model model_;
    };

    struct ShaderKey {
        std::string vertex_path;
        std::string fragment_path;
        bool operator==(const ShaderKey& other) const {
            return vertex_path == other.vertex_path &&
                   fragment_path == other.fragment_path;
        }
    };

    struct ShaderKeyHash {
        size_t operator()(const ShaderKey& key) const {
            return std::hash<std::string>()(key.vertex_path) ^
                (std::hash<std::string>()(key.fragment_path) << 1);
        }
    };


    // Global Data Storage
    static std::vector<Mesh> meshes_;
    static std::vector<Texture> textures_;
    static std::vector<Material> materials_;
    static std::vector<Model> models_;
    static std::vector<Shader> shaders_;

    // Data Caches
    static std::unordered_map<std::string, TextureID> texture_cache_;
    static std::unordered_map<std::string, ModelID> model_cache_;
    static std::unordered_map<ShaderKey, ShaderID, ShaderKeyHash> shader_cache_;

    // Model loading
    static ModelID loadModelFromFile(const std::filesystem::path& path);
    static void processNode(aiNode* node, const aiScene* scene, LoadContext& context);
    static void processMesh(aiMesh* mesh, const aiScene* scene, LoadContext& context);
    static std::vector<TextureSlot> loadMaterialTextures(
            aiMaterial* mat, 
            aiTextureType type, 
            LoadContext& context);

    // Texture loading
    static TextureID loadTextureFromFile(const std::filesystem::path& path);

    // Shader loading
    static ShaderID loadShaderFromFile(
            const std::filesystem::path& vertex_path, 
            const std::filesystem::path& fragment_path);

    static DefaultShaders defaultShaders_;
};
