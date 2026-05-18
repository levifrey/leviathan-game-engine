#include "Mesh.h"
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "AssetManager.h"


Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    data_ = make_shared<MeshData>();
    data_->vertices_ = vertices;
    data_->indices_ = indices;
    textures_ = textures;
    setUpMesh();
}

/*
 * used when you want to upload custom textures not part of an object file
 */
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices) {
    data_ = make_shared<MeshData>();
    data_->vertices_ = vertices;
    data_->indices_ = indices;
    setUpMesh();
}

void Mesh::setUpMesh() {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, data_->vertices_.size() * sizeof(Vertex), &data_->vertices_[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_->indices_.size() * sizeof(unsigned int), &data_->indices_[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position_)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal_)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoords_)));

    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int bufferNr = 1;
    for (unsigned int i = 0; i < textures_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        string name;
        if (textures_[i].getType() == TextureType::DIFFUSE) {
            name = "diffuse" + std::to_string(diffuseNr++);
        } else if (textures_[i].getType() == TextureType::SPECULAR) {
            name = "specular" + std::to_string(specularNr++);
        }

        shader.setInt(("material." + name).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].getID());
    }
    
    if (specularNr == 1) {
        glActiveTexture(GL_TEXTURE0 + textures_.size());
        string name = "material.specular1";
        shader.setInt(name.c_str(), textures_.size());
        glBindTexture(GL_TEXTURE_2D, AssetManager::getTexture("black_texture")->getID());
    }
    if (diffuseNr == 1) {
        int number = textures_.size();
        if (specularNr == 1) { number++; }
        glActiveTexture(GL_TEXTURE0 + number);
        string name = "material.diffuse1";
        shader.setInt(name.c_str(), number);
        glBindTexture(GL_TEXTURE_2D, AssetManager::getTexture("black_texture")->getID());
    }
    
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, data_->indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
