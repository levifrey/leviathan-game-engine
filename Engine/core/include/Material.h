#pragma once
#include <vector>
#include "AssetTypes.h"

enum TextureType {
    DIFFUSE,
    SPECULAR,
    CUBEMAP
};

struct TextureSlot {
    TextureID ID_;
    TextureType type_;
};

struct Material {
    std::vector<TextureSlot> texture_slots_;
    float shininess_;
};

