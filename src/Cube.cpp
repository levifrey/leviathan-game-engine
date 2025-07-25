#include "Cube.h"

Cube::Cube(Model* model, Shader* shader, Game* game) : GameObject(model, shader, game) {}

void Cube::update() {
    getShader()->use();
    getShader()->setMat4("model", getTranslation());
    getShader()->setMat4("view", getGame()->getCamera()->getView());
    getShader()->setMat4("projection", getGame()->getCamera()->getProjection());
    getShader()->setFloat("material.shininess", 32.0f);
    
    getShader()->setVec3("light.position", glm::vec3(5.0f, 1.0f, 11.0f));
    getShader()->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    getShader()->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    getShader()->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    getShader()->setVec3("viewPos", getGame()->getCamera()->getPosition());
}
