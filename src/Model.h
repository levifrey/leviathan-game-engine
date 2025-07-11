#ifndef MODEL_H
#define MODEL_H
#include "Shader.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
class Model {
    public:
        Model(float vertices[], size_t vertices_size, unsigned int indices[], size_t indices_size, int vertex_size, Shader& shader);
        void render();
        void rotate(float radians, glm::vec3 axis);
        void translate(glm::vec3 translation);
        void translate(float x, float y, float z);
        void scale(glm::vec3 factor);
        void scale(float factor);
        void addTexture(const char* path);
        void makeVertexAttribute(float atribute_size);
        Shader* getShader() { glUseProgram(shader_->ID); return shader_; }
        void printModelMatrix();
    private:
        unsigned int VBO_;
        unsigned int VAO_;
        unsigned int EBO_;
        size_t current_pointer_ = 0;
        unsigned int  current_id_ = 0;
        int vertex_size_;
        int vertex_count_;
        Shader* shader_;
        unsigned int texture_;
        bool has_texture_ = false;
        glm::mat4 model_matrix_ = glm::mat4(1.0f);

};

#endif
