#include <vector>
#include "Model.h"
#include "Shapes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
Model createCube(float size) {
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> normals;
    std::vector<glm::vec2> textures;

    for (float rot = 0; rot < 360; rot += 90) {
        float radians = glm::radians(rot);
        glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, axis);

        // top left
        vertices.push_back(size * (rotation * glm::vec4(-0.5f, 0.5f, -0.5f, 0.0f)));
        textures.push_back(glm::vec2(0.0f, 1.0f));

        // top right
        vertices.push_back(size * (rotation * glm::vec4(0.5f, 0.5f, -0.5f, 0.0f)));
        textures.push_back(glm::vec2(1.0f, 1.0f));

        // bottom right (repeated)
        for (int i = 0; i < 2; i++) {
            vertices.push_back(size * (rotation * glm::vec4(0.5f, -0.5f, -0.5f, 0.0f)));
            textures.push_back(glm::vec2(1.0f, 0.0f));
        }

        // bottom left
        vertices.push_back(size * (rotation * glm::vec4(-0.5f, -0.5f, -0.5f, 0.0f)));
        textures.push_back(glm::vec2(0.0f, 0.0f));

        // top left again
        vertices.push_back(size * (rotation * glm::vec4(-0.5f, 0.5f, -0.5f, 0.0f)));
        textures.push_back(glm::vec2(0.0f, 1.0f));

        // normals
        for (int i = 0; i < 6; i++) {
            normals.push_back(rotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
        }   
    }

    for (float rot = 0; rot < 360; rot += 180) {
        float radians = glm::radians(rot);
        glm::vec3 axis = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, axis);

        // top left
        vertices.push_back(size * (rotation * glm::vec4(-0.5f, 0.5f, 0.5f, 0.0f)));
        textures.push_back(glm::vec2(0.0f, 1.0f));

        // top right
        vertices.push_back(size * (rotation * glm::vec4(0.5f, 0.5f, 0.5f, 0.0f)));
        textures.push_back(glm::vec2(1.0f, 1.0f));

        // bottom right (repeated)
        for (int i = 0; i < 2; i++) {
            vertices.push_back(size * (rotation * glm::vec4(0.5f, 0.5f, -0.5f, 0.0f)));
            textures.push_back(glm::vec2(1.0f, 0.0f));
        }

        // bottom left
        vertices.push_back(size * (rotation * glm::vec4(-0.5f, 0.5f, -0.5f, 0.0f)));
        textures.push_back(glm::vec2(0.0f, 0.0f));

        // top left again
        vertices.push_back(size * (rotation * glm::vec4(-0.5f, 0.5f, 0.5f, 0.0f)));
        textures.push_back(glm::vec2(0.0f, 1.0f));

        // normals 
        for (int i = 0; i < 6; i++) {
            normals.push_back(rotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
        }
    }

    std::vector<float> vertex_list;
    std::vector<unsigned int> indices;
    for (int i = 0; i < 36; i++) {
        vertex_list.push_back(vertices[i].x);
        vertex_list.push_back(vertices[i].y);
        vertex_list.push_back(vertices[i].z);
        vertex_list.push_back(textures[i].x);
        vertex_list.push_back(textures[i].y);
        vertex_list.push_back(normals[i].x);
        vertex_list.push_back(normals[i].y);
        vertex_list.push_back(normals[i].z);
        indices.push_back(i);
    }

    Model cube(vertex_list.data(), vertex_list.size() * sizeof(float), indices.data(), indices.size() * sizeof(int), 8);
    cube.makeVertexAttribute(3);
    cube.makeVertexAttribute(2);
    cube.makeVertexAttribute(3);
    return cube;
}   
