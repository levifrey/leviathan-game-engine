#pragma once

#include <filesystem>
#include "Texture.h"    
#include <array>
#include <glad/glad.h>

struct TextureLoadContext {
    GLenum internalFormat = GL_RGBA;
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;
    GLenum wrapS = GL_REPEAT; // GL_REPEAT, GL_CLAMP_TO_EDGE
    GLenum wrapT = GL_REPEAT; // GL_REPEAT, GL_CLAMP_TO_EDGE
    GLenum wrapR = GL_REPEAT; // GL_REPEAT, GL_CLAMP_TO_EDGE
    GLenum minFilter = GL_LINEAR; // GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR
    GLenum magFilter = GL_LINEAR; // GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR
};

class TextureLoader {
    public:
        static Texture loadTextureFromFile(
                const std::filesystem::path& path, TextureLoadContext context);
        static Texture loadTextureFromData(
                const unsigned char* data,
                unsigned int width,
                unsigned int height);

        // posx, negx, posy, negy, posz, negz
        static Texture loadCubemapFromFile(std::array<std::filesystem::path, 6> paths);
        static Texture createEmptyCubemap(unsigned int size, TextureLoadContext context);
};
