#ifndef TEXTURE_H
#define TEXTURE_H
#include <filesystem>

enum TextureType {
    DIFFUSE,
    SPECULAR,
    DEFAULT,
    BUFFER
};

class Texture {
    public:
        Texture() {}
        Texture(std::filesystem::path path, TextureType type, bool repeated = false);
        Texture(unsigned char* data, int width, int height, TextureType type);
        void init(std::filesystem::path path, TextureType type, bool repeated = false);
        void init(unsigned char* data, int width, int height, TextureType type);
        unsigned int getID() const { return ID_; }
        TextureType getType() const { return type_; } 
    private:
        unsigned int ID_;
        TextureType type_;
};

#endif
