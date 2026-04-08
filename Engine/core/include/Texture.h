#ifndef TEXTURE_H
#define TEXTURE_H
#include <filesystem>

class Texture {
    public:
        Texture(std::filesystem::path path);
        unsigned int getID() const { return ID_; }
    private:
        unsigned int ID_;
};

#endif
