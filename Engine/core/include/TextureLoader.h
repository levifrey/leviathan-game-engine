#pragma once

#include <filesystem>
#include "Texture.h"
#include <array>

class TextureLoader {
    public:
        static Texture loadTextureFromFile(const std::filesystem::path& path);
        static Texture loadTextureFromData(
                const unsigned char* data,
                unsigned int width,
                unsigned int height);

        // posx, negx, posy, negy, posz, negz
        static Texture loadCubemapFromFile(std::array<std::filesystem::path, 6> paths);
};
