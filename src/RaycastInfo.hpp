#pragma once
#include "BlockManager.hpp"
#include "hd/Math/hdMathUtils.hpp"

struct RaycastInfo {
    RaycastInfo() : blockPos(0, 0, 0) {}

    hd::RayIntersectAABBInfo intersection;
    glm::ivec3 blockPos;
    BlockType blockType;
};