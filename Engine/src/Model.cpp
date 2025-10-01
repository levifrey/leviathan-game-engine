#include "Model.h"
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

Model::Model(float vertices[], size_t vertices_size, unsigned int indices[], size_t indices_size, int vertex_size) {
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
}

void Model::makeVertexAttribute(float attribute_size) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glVertexAttribPointer(current_id_, attribute_size, GL_FLOAT, GL_FALSE, vertex_size_ * sizeof(float), (void*)current_pointer_);
    glEnableVertexAttribArray(current_id_);
    current_id_++;
    current_pointer_ += attribute_size * sizeof(float);
}

void Model::draw() {
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glDrawElements(GL_TRIANGLES, vertex_count_, GL_UNSIGNED_INT, 0);
}
