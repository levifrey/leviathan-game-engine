#include <iostream>
#include <glm/glm.hpp>
#include "Engine.h"
#include "LightBehavior.h"

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
    GameObject obj(&game);
    obj.addComponent<Transform>();
    obj.addComponent<Renderer>(&cube, &light_shader);
    obj.getComponent<Transform>()->translate(glm::vec3(0.0f, 0.0f, 5.0f));
    obj.getComponent<Renderer>()->addTexture(&obj_diffuse, 0);
    obj.getComponent<Renderer>()->addTexture(&obj_specular, 1);
    game.addGameObject(&obj); 
    
    GameObject light(&game);
    light.addComponent<Transform>();
    light.addComponent<Renderer>(&cube, &default_shader);
    light.addComponent<AreaLight>();
    light.addComponent<LightBehavior>();
    game.addGameObject(&light);
    game.setLightSource(light.getComponent<AreaLight>());
        
    // Game Loop Start
    game.Loop();
}
