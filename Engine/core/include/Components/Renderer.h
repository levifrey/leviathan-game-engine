#pragma once

#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include <memory>
#include "RenderEffects/AllRenderEffects.h"


class Renderer : public Component {
    public:
        Renderer(Model* model, Shader* shader);
        void render();
        void update() override {}
        Model* getModel() { return model_; }
        Shader* getShader() { return shader_; }

        template<typename T, typename... Args>
        void setRenderEffect(Args&&... args) {
            effect_ = std::make_unique<T>(std::forward<Args>(args)...);
        }

    private:
        Model* model_;
        Shader* shader_;
        std::unique_ptr<RenderEffect> effect_ = std::make_unique<BasicEffect>();
};

