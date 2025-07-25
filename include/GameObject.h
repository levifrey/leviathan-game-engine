#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>
#include <glm/glm.hpp>

class Game;

class GameObject {
    public:
        GameObject(Model* model, Shader* shader, Game* game);
        void render();
        void translate(glm::vec3 translation);
        void rotate(float radians, glm::vec3 axis);
        void scale(glm::vec3 factor);
        Shader* getShader();
        Game* getGame();
        glm::mat4 getTranslation();
        void addTexture(Texture* texture, int index);

        virtual void update() = 0;
    private:
        Model* model_;
        Shader* shader_;
        std::vector<Texture*> textures_;
        Game* game_;
        glm::mat4 translation_ = glm::mat4(1.0f);
};

#endif
