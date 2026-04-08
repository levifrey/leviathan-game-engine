#ifndef MODEL_H
#define MODEL_H
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>

class Model {
    public:
        Model(float vertices[], size_t vertices_size, unsigned int indices[], size_t indices_size, int vertex_size);
        void draw();
        void makeVertexAttribute(float atribute_size);
    private:
        unsigned int VBO_;
        unsigned int VAO_;
        unsigned int EBO_;
        size_t current_pointer_ = 0;
        unsigned int  current_id_ = 0;
        int vertex_size_;
        int vertex_count_;

};

#endif
