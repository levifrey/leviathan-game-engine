#ifndef TEXTURE_H
#define TEXTURE_H
#include <filesystem>

enum TextureType {
    DIFFUSE,
    SPECULAR,
    DEFAULT
};

class Texture {
    public:
        Texture(std::filesystem::path path, TextureType type, bool repeated = false);
        Texture(unsigned char* data, int height, int width, TextureType type);
        unsigned int getID() const { return ID_; }
        TextureType getType() const { return type_; } 
    private:
        unsigned int ID_;
        TextureType type_;
};

#endif
