#pragma once

enum class TextureBinding : int {
    Diffuse     = 0,
    Specular    = 1,
    Skybox      = 2,
    PostProcess = 3
};

enum class UBOBinding : int {
    Lights = 0,
    Camera = 1
};

