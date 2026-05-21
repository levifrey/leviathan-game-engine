#include "Components/Renderer.h"
#include "Components/Transform.h"
#include "GameObject.h"
#include "Game.h"
#include "AssetManager.h"

Renderer::Renderer(ModelID model_id, ShaderID shader_id) : 
    model_id_(model_id),
    shader_id_(shader_id)
{}

void Renderer::render() {
    const Shader& shader = AssetManager::getShader(shader_id_);
    shader.use();
    glm::mat4 transform = getGameObject()->getComponent<Transform>()->getWorldMatrix();
    shader.setMat4("model", transform);
    getGameObject()->getGame()->applyGlobalUniforms(shader);
    const Model& model = AssetManager::getModel(model_id_);

    for (int i = 0; i < model.parts_.size(); i++) {
        const Mesh& mesh = AssetManager::getMesh(model.parts_[i].mesh_);
        const Material& material = AssetManager::getMaterial(model.parts_[i].material_);
        useMaterial(material, shader);
        
        if (outline_.active_) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
        }

        drawMesh(mesh);

        if (outline_.active_) {
            drawOutline(mesh, transform);
            shader.use();
        }
    }
}

void Renderer::useMaterial(const Material& material, const Shader& shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int bufferNr = 1;
    for (unsigned int i = 0; i < material.textures_slots_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string name;
        if (material.textures_slots_[i].type_ == TextureType::DIFFUSE) {
            name = "diffuse" + std::to_string(diffuseNr++);
        } else if(material.textures_slots_[i].type_ == TextureType::SPECULAR) {
            name = "specular" + std::to_string(specularNr++);
        }
        shader.setInt(("material." + name).c_str(), i);
        const Texture& texture = AssetManager::getTexture(material.textures_slots_[i].ID_);
        glBindTexture(GL_TEXTURE_2D, texture.ID_);
    }
    glActiveTexture(GL_TEXTURE0);
    shader.setFloat("material.shininess", material.shininess_);
}

void Renderer::drawMesh(const Mesh& mesh) {
    glBindVertexArray(mesh.VAO_);
    glDrawElements(GL_TRIANGLES, mesh.indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::drawOutline(const Mesh& mesh, glm::mat4 transform) {
    const Shader& outline_shader = AssetManager::getShader(AssetManager::getShaders().outline_);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0x00);
    float factor = outline_.width_ + 1.0f;
    glm::mat4 scaled_transform = glm::scale(transform, glm::vec3(factor)); 
    outline_shader.use();
    outline_shader.setVec4("color", outline_.color_);
    outline_shader.setMat4("model", scaled_transform);
    drawMesh(mesh);
    
    glStencilFunc(GL_ALWAYS, 1, 0xFF);

}
