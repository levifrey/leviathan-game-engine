#ifndef MESH_H
#define MESH_H
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include <memory>
using namespace std;
struct Vertex {
    glm::vec3 position_;
    glm::vec3 normal_;
    glm::vec2 texCoords_;
};

struct MeshData {
    vector<Vertex> vertices_;
    vector<unsigned int> indices_;
};

class Mesh {
    public:
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
        void draw(Shader &shader);
        void setUpMesh();
        vector<Texture> textures_;
        void addTexture(Texture texture) { textures_.push_back(texture); }
    private:
        unsigned int VBO_;
        unsigned int VAO_;
        unsigned int EBO_;
        shared_ptr<MeshData> data_;
};

#endif
