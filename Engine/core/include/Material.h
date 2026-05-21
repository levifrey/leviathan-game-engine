#pragma once
#include <vector>
#include "AssetTypes.h"

enum TextureType {
    DIFFUSE,
    SPECULAR
};

struct TextureSlot {
    TextureID ID_;
    TextureType type_;
};

struct Material {
    std::vector<TextureSlot> textures_slots_;
    float shininess_;
};

