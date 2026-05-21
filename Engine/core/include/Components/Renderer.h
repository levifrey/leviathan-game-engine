#pragma once

#include "Component.h"
#include "AssetTypes.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Transform.h"

struct OutlineConfig {
    bool active_;
    glm::vec4 color_;
    float width_;
};



class Renderer : public Component {
    public:
        Renderer(ModelID model, ShaderID shader);
        void render();
        void update() override {}
        ModelID getModel() { return model_id_; }
        ShaderID getShader() { return shader_id_; }
        OutlineConfig& getOutlineConfig() { return outline_; }
    private:
        ModelID model_id_;
        ShaderID shader_id_;
        void useMaterial(const Material& material, const Shader& shader);
        void drawMesh(const Mesh& mesh);

        // Render Settings:
        OutlineConfig outline_{false, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.05f};
        void drawOutline(const Mesh& mesh, glm::mat4 transform);
};

