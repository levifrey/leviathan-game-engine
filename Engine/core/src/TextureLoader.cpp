#include "TextureLoader.h"

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>

Texture TextureLoader::loadTextureFromFile(const std::filesystem::path& path) {   
    int width, height, nrChannels;
    unsigned int ID;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    bool repeated = true;
    if (repeated) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else { 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "FAILED TO LOAD TEXTURE: " << path.string() << std::endl;
    }
    stbi_image_free(data);
    std::cout << "-- generated texture from: " << path.string() << ", with ID: " << ID << std::endl;
    return {ID};
}

Texture TextureLoader::loadTextureFromData(const unsigned char* data, unsigned int width, unsigned int height) {
    unsigned int ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return {ID};
}

