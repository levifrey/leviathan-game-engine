#ifndef RENDERER_H
#define RENDERER_H

#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>

class Renderer : public Component {
    public:
        Renderer(Model* model, Shader* shader);
        void addTexture(Texture* texture, int index);
        void render();
        void update() override {}
    private:
        Model* model_;
        Shader* shader_;
        std::vector<Texture*> textures_;

};

#endif
