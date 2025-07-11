#include "Model.h"
#include "../include/stb_image.h"
#include <iostream>
#include <string>


Model::Model(float vertices[], size_t vertices_size, unsigned int indices[], size_t indices_size, int vertex_size, Shader& shader) {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
    
    vertex_size_ = vertex_size;
    vertex_count_ = vertices_size / vertex_size_;
    shader_ = &shader;
}

void Model::makeVertexAttribute(float attribute_size) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glVertexAttribPointer(current_id_, attribute_size, GL_FLOAT, GL_FALSE, vertex_size_ * sizeof(float), (void*)current_pointer_);
    glEnableVertexAttribArray(current_id_);
    current_id_++;
    current_pointer_ += attribute_size * sizeof(float);
}

void Model::addTexture(const char* path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "FAILED TO LOAD TEXTURE: " << path << std::endl; 
    }
    stbi_image_free(data);
    has_texture_ = true;
}

void Model::render() {
    glUseProgram(shader_->ID);
    shader_->setMat4("model", model_matrix_);
    if (has_texture_) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);
    }
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glDrawElements(GL_TRIANGLES, vertex_count_, GL_UNSIGNED_INT, 0);
}

void Model::rotate(float radians, glm::vec3 axis) {
    model_matrix_ = glm::rotate(model_matrix_, glm::radians(radians), axis);
}

void Model::translate(glm::vec3 translation) {
    model_matrix_ = glm::translate(model_matrix_, translation);
}

void Model::translate(float x, float y, float z) {
    model_matrix_ = glm::translate(model_matrix_, glm::vec3(x, y, z));
}

void Model::scale(glm::vec3 factor) {
    model_matrix_ = glm::scale(model_matrix_, factor);
}

void Model::scale(float factor) {
    model_matrix_ = glm::scale(model_matrix_, glm::vec3(factor, factor, factor));
}

void Model::printModelMatrix() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << model_matrix_[j][i] << " ";
        }
        std::cout << std::endl;
    }
}
