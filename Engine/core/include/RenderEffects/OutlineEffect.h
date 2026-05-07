#pragma once
#include "RenderEffects/RenderEffect.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "Components/Transform.h"

class OutlineEffect : public RenderEffect {
    public:

    OutlineEffect(glm::vec4 color, float width) {
        color_ = color;
        width_ = width;
    }

    void render(Model* model, Shader* shader, GameObject* obj) {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        // draw original object and write ones for every fragment
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        drawObject(model, shader, obj);
        
        // draw flat color where object is not
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        //glDisable(GL_DEPTH_TEST);

        // scale object and draw
        float factor = 1.0f + width_;
        Transform* t = obj->getComponent<Transform>();
        t->scale(factor);
        
        Shader* outline_shader = AssetManager::getShader("singleColor_shader");
        outline_shader->use();
        outline_shader->setVec4("color", color_);

        drawObject(model, AssetManager::getShader("singleColor_shader"), obj);

        // reset, downscale object
        t->scale(1.0f/factor);
        glStencilMask(0x00);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);
    }

    private:

    glm::vec4 color_;
    float width_;

};
