#pragma once

#include <filesystem>
#include "Texture.h"

class TextureLoader {
    public:
        static Texture loadTextureFromFile(const std::filesystem::path& path);
        static Texture loadTextureFromData(
                const unsigned char* data,
                unsigned int width,
                unsigned int height);
};
