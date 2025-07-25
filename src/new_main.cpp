#include "Game.h"
#include "Shapes.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Cube.h"
#include <iostream>
#include <glm/glm.hpp>

int main(int, char**) {

    // Game Init
    Game game(800, 800);
    game.getCamera()->setYaw(90.0f);

    // Models
    Model cube = createCube(1.0f);

    // Shaders
    Shader default_shader("../resources/shaders/default.vert", "../resources/shaders/default.frag");
    Shader light_shader("../resources/shaders/light.vert", "../resources/shaders/light.frag");
    light_shader.reserveTexture("material.diffuse", 0);
    light_shader.reserveTexture("material.specular", 1);

    // Textures
    Texture obj_diffuse("../resources/textures/container2.jpg");
    Texture obj_specular("../resources/textures/container2_specular.jpg");
     
    // Game object Init
    Cube gameObj(&cube, &light_shader, &game);
    gameObj.translate(glm::vec3(0.0f, 0.0f, 10.0f));
    gameObj.addTexture(&obj_diffuse, 0);
    gameObj.addTexture(&obj_specular, 1);
    game.addGameObject(&gameObj); 
    
    // Game Loop Start
    game.Loop();
}
