#include <vector>
#include "Mesh.h"
#include "Shapes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Mesh Shapes::createQuad() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
    vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));

    vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
    vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
    vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

    textures.push_back(glm::vec2(0.0f, 1.0f));
    textures.push_back(glm::vec2(0.0f, 0.0f));
    textures.push_back(glm::vec2(1.0f, 0.0f));
    textures.push_back(glm::vec2(0.0f, 1.0f));
    textures.push_back(glm::vec2(1.0f, 0.0f));
    textures.push_back(glm::vec2(1.0f, 1.0f));

    std::vector<Vertex> v_list;
    std::vector<unsigned int> i_list;

    for (unsigned int i = 0; i < 6; i++) {
        Vertex v;
        v.position_.x = vertices[i].x;
        v.position_.y = vertices[i].y;
        v.position_.z = vertices[i].z;
        v.texCoords_.x = textures[i].x;
        v.texCoords_.y = textures[i].y;
        v_list.push_back(v);
        i_list.push_back(i);
    }
    Mesh quad(v_list, i_list);
    return quad;
}

Mesh Shapes::createCube(float size) {
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

    std::vector<Vertex> vertex_list;
    std::vector<unsigned int> indices;
    for (int i = 0; i < 36; i++) {
        Vertex v;
        v.position_.x = vertices[i].x;
        v.position_.y = vertices[i].y;
        v.position_.z = vertices[i].z;

        v.normal_.x = normals[i].x;
        v.normal_.y = normals[i].y;
        v.normal_.z = normals[i].z;

        v.texCoords_.x = textures[i].x;
        v.texCoords_.y = textures[i].y;
        vertex_list.push_back(v);
        indices.push_back(i);
    }

    Mesh cube(vertex_list, indices);
    return cube;
}   

Mesh Shapes::createPlane(float size) {
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> normals;
    std::vector<glm::vec2> textures;
    
    vertices.push_back(glm::vec4(size/2.0f, 0.0f, -size/2.0f, 0.0f));
    vertices.push_back(glm::vec4(size/2.0f, 0.0f, size/2.0f, 0.0f));
    vertices.push_back(glm::vec4(-size/2.0f, 0.0f, size/2.0f, 0.0f));
    vertices.push_back(glm::vec4(-size/2.0f, 0.0f, size/2.0f, 0.0f));
    vertices.push_back(glm::vec4(-size/2.0f, 0.0f, -size/2.0f, 0.0f));
    vertices.push_back(glm::vec4(size/2.0f, 0.0f, -size/2.0f, 0.0f));
    
    for (int i = 0; i < 6; i++) {
        normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    }

    textures.push_back(glm::vec2(0.0f, size));
    textures.push_back(glm::vec2(size, size));
    textures.push_back(glm::vec2(size, 0.0f));
    textures.push_back(glm::vec2(size, 0.0f));
    textures.push_back(glm::vec2(0.0f, 0.0f));
    textures.push_back(glm::vec2(0.0f, size));
    
    std::vector<Vertex> vertex_list;
    std::vector<unsigned int> indices_list;
    for (unsigned int i = 0; i < 6; i++) {
        Vertex v;
        v.position_.x = vertices[i].x;
        v.position_.y = vertices[i].y;
        v.position_.z = vertices[i].z;

        v.normal_.x = normals[i].x;
        v.normal_.y = normals[i].y;
        v.normal_.z = normals[i].z;

        v.texCoords_.x = textures[i].x;
        v.texCoords_.y = textures[i].y;

        vertex_list.push_back(v);
        indices_list.push_back(i);
    }

    Mesh plane(vertex_list, indices_list);
    return plane;
}
