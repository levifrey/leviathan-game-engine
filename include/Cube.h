#ifndef CUBE_H
#define CUBE_H
#include "GameObject.h"
#include "Model.h"
#include "Game.h"

class Cube : public GameObject {
    public:
        Cube(Model* model, Shader* shader, Game* game);

        void update() override;
};
#endif
