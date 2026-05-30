#include "AssetManager.h"
#include "Mesh.h"
#include "PathUtils.h"
#include "Shapes.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>


std::vector<Mesh> AssetManager::meshes_;
std::vector<Texture> AssetManager::textures_;
std::vector<Material> AssetManager::materials_;
std::vector<Model> AssetManager::models_;
std::vector<Shader> AssetManager::shaders_;

std::unordered_map<AssetManager::ShaderKey, ShaderID, AssetManager::ShaderKeyHash> AssetManager::shader_cache_;
std::unordered_map<std::string, ModelID> AssetManager::model_cache_;
std::unordered_map<std::string, TextureID> AssetManager::texture_cache_;

AssetManager::DefaultShaders AssetManager::defaultShaders_;
AssetManager::DefaultGeometry AssetManager::defaultGeometry_;
AssetManager::DefaultTextures AssetManager::defaultTextures_;
AssetManager::DefaultMaterials AssetManager::defaultMaterials_;


void AssetManager::init() {
    /*
     *  Load Engine Shader
     */
    defaultShaders_.fallback_ = loadShader(
            PathUtils::shaderDir / "camera.vert",
            PathUtils::shaderDir / "default.frag");

    defaultShaders_.outline_ = loadShader(
            PathUtils::shaderDir / "camera.vert", 
            PathUtils::shaderDir / "singleColor.frag");

    defaultShaders_.screen_ = loadShader(
            PathUtils::shaderDir / "screen.vert",
            PathUtils::shaderDir / "screen.frag");
    
    /*
     *  Load Engine Geometry
     */
    defaultGeometry_.cube_ = storeMesh(Shapes::createCube(1.0f));
    defaultGeometry_.plane_ = storeMesh(Shapes::createPlane(1.0f));
    defaultGeometry_.quad_ = storeMesh(Shapes::createQuad());

    /*
     *  Load Engine Textures
     */
    unsigned char black[] = {0,0,0,0};
    defaultTextures_.fallback_ = storeTextureFromData(black, 1, 1);

    /*
     * Load Engine Materials
     */
    defaultMaterials_.textureless_ = storeMaterial({{},1.0f});
    
}

/*
 *  Get assets from ID
 */

const Mesh& AssetManager::getMesh(MeshID id) {
    return meshes_.at(id);    
}

const Texture& AssetManager::getTexture(TextureID id) {
    return textures_.at(id);
}

const Material& AssetManager::getMaterial(MaterialID id) {
    return materials_.at(id);
};

const Model& AssetManager::getModel(ModelID id) {
    return models_.at(id);
}

const Shader& AssetManager::getShader(ShaderID id) {
    return shaders_.at(id);
}

/*
 *  Store Assets
 */
MeshID AssetManager::storeMesh(Mesh mesh) {
    meshes_.push_back(mesh);
    return (MeshID)meshes_.size()-1;
}

MaterialID AssetManager::storeMaterial(Material material) {
    materials_.push_back(material);
    return (MaterialID)materials_.size()-1;
}

ModelID AssetManager::storeModel(Model model) {
    models_.push_back(model);
    return (ModelID)models_.size()-1;
}

TextureID AssetManager::storeTexture(Texture texture) {
    textures_.push_back(texture);
    return (TextureID)textures_.size()-1;
}


/*
 *  Load asset for the first time or pull from cache if already loaded somewherer else
 */

ModelID AssetManager::loadModel(const std::filesystem::path& path) {
    auto it = model_cache_.find(path.string());
    if (it != model_cache_.end()) {
        return it->second;
    } else {
        return loadModelFromFile(path); 
    }
}

TextureID AssetManager::loadTexture(const std::filesystem::path& path) {
    auto it = texture_cache_.find(path.string());
    if (it != texture_cache_.end()) {
        return it->second;
    } else {
        return loadTextureFromFile(path);
    }
}


ShaderID AssetManager::loadShader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path) {
    auto it = shader_cache_.find({vertex_path.string(), fragment_path.string()});
    if(it != shader_cache_.end()) {
        return it->second;
    } else {
        return loadShaderFromFile(vertex_path, fragment_path);
    }
}

/*
 * Model Loading Pipeline Code
 */

ModelID AssetManager::loadModelFromFile(const std::filesystem::path& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate /*| aiProcess_FlipUVs*/);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }

    LoadContext context;
    context.directory_ = path.parent_path();
    processNode(scene->mRootNode, scene, context);
    models_.push_back(std::move(context.model_));
    model_cache_.insert({path.string(), models_.size()-1});
    return (ModelID)models_.size()-1;
}


void AssetManager::processNode(aiNode* node, const aiScene* scene, LoadContext& context) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, context); 
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, context);
    }
}

void AssetManager::processMesh(aiMesh* mesh, const aiScene* scene, LoadContext& context) { 
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position_ = vector;
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal_ = vector;
        }


        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords_ = vec;
        } else {
            vertex.texCoords_ = glm::vec2(0.0, 0.0);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    // Create the new mesh and assign it an ID
    meshes_.push_back({vertices, indices});
    MeshID mesh_id = meshes_.size()-1;

    auto it = context.material_cache_.find(mesh->mMaterialIndex);
    MaterialID mat_id;

    // Use cached material
    if (it != context.material_cache_.end()) {
        mat_id = it->second;
    }
    
    // Create a new material and assign a new ID
    else {
        Material new_material;

        std::vector<TextureSlot> new_mat_textures;
        float shininess = 1.0f;
        
        // Get textures
        aiMaterial* assimp_material = scene->mMaterials[mesh->mMaterialIndex];
        vector<TextureSlot> diffuse_maps = loadMaterialTextures(assimp_material, aiTextureType_DIFFUSE, context);
        vector<TextureSlot> specular_maps = loadMaterialTextures(assimp_material, aiTextureType_SPECULAR, context);
        new_mat_textures.insert(new_mat_textures.end(), diffuse_maps.begin(), diffuse_maps.end());
        new_mat_textures.insert(new_mat_textures.end(), specular_maps.begin(), specular_maps.end());

        // Get shininess
        if (assimp_material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
            if (shininess <= 0.0f)
                shininess = 1.0f;
        }
        
        // Fill the Material object, add it to the assets, and cache it
        new_material.texture_slots_ = std::move(new_mat_textures);
        new_material.shininess_ = shininess;
        materials_.push_back(std::move(new_material));
        std::cout << "diffuse" <<std::endl;
        mat_id = materials_.size()-1;
        context.material_cache_.insert({mesh->mMaterialIndex, mat_id});
    }
    
    context.model_.parts_.push_back({mesh_id, mat_id});
}


std::vector<TextureSlot> AssetManager::loadMaterialTextures(aiMaterial* mat, aiTextureType type, LoadContext& context) {
    TextureType new_type;
    if(type == aiTextureType_DIFFUSE) {
        new_type = TextureType::DIFFUSE;
    } else if(type == aiTextureType_SPECULAR) {
        new_type = TextureType::SPECULAR;
    }

    std::vector<TextureSlot> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        string sub_path = str.C_Str();
        const std::filesystem::path new_path = context.directory_ / sub_path;
        TextureID id = loadTexture(new_path);
        textures.push_back({id, new_type});
    }
    return textures;
}

/*
 * Texture Loading Code
 */

TextureID AssetManager::loadTextureFromFile(const std::filesystem::path& path) {   
    int width, height, nrChannels;
    unsigned int ID;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    bool repeated = true;
    if (repeated) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else { 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "FAILED TO LOAD TEXTURE: " << path.string() << std::endl;
        return defaultTextures_.fallback_;
    }
    stbi_image_free(data);
    std::cout << "-- generated texture from: " << path.string() << ", with ID: " << ID << std::endl;

    textures_.push_back({ID});
    texture_cache_.insert({path.string(), (TextureID)textures_.size()-1});
    return textures_.size()-1;
}

TextureID AssetManager::storeTextureFromData(const unsigned char* data, int width, int height) {
    unsigned int ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0); 
    textures_.push_back({ID});
    return textures_.size()-1;
}

/*
 * Shader Loading code
 */

ShaderID AssetManager::loadShaderFromFile(
        const std::filesystem::path& vertex_path, 
        const std::filesystem::path& fragment_path) 
{
    unsigned int ID;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertex_path.string());
        fShaderFile.open(fragment_path.string());
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } 
    catch(std::ifstream::failure e) {
        std::cout << "FAILED TO READ FROM FILE" << std::endl;
        return defaultShaders_.fallback_;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
 
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::COMPILATION_FAILED (" << vertex_path.string() << ")" << std::endl;
        std::cerr << infoLog << std::endl;
        return defaultShaders_.fallback_;
    }


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED (" << fragment_path.string() << ")" << std::endl;
        std::cerr << infoLog << std::endl;
        return defaultShaders_.fallback_;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILURE" << std::endl;
        return defaultShaders_.fallback_;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    shaders_.push_back({ID});
    shader_cache_.insert({{vertex_path.string(), fragment_path.string()}, (ShaderID)shaders_.size()-1});
    return (ShaderID)shaders_.size()-1;
}
