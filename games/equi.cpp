#include "Engine.h"
#include <iostream>

int main() {
    Game game(1500, 900);

    // Shaders
    ShaderID reflect = AssetManager::loadShader(
            PathUtils::shaderDir / "reflect/reflect.vert",
            PathUtils::shaderDir / "reflect/reflect.frag");

    // Textures
    TextureID cubemap = AssetManager::storeCubemap(
        CubemapConverter::equirectangularToCubemap(PathUtils::textureDir / "milky.jpg")
    );

    game.setSkybox(cubemap);
    game.Loop();
}


