#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
    public:
        Texture(const char* path);
        unsigned int getID() const { return ID_; }
    private:
        unsigned int ID_;
};

#endif
