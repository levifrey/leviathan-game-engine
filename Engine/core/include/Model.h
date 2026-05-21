#pragma once
#include <vector>
#include "AssetTypes.h"


struct RenderPart {
    MeshID mesh_;
    MaterialID material_;
};

struct Model {
    std::vector<RenderPart> parts_;
};
