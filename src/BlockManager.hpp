#pragma once
#include "hd/Graphics/hdRenderContext.hpp"

enum class BlockType : uint8_t {
    Air,
    Grass,
    Dirt,
    Stone
};

class BlockManager {
public:
    BlockManager(hd::RenderContext &renderContext);
    ~BlockManager();

    const hd::HTexture2DArray &getTextureArray() const;

private:
    hd::RenderContext &mRenderContext;
    hd::HTexture2DArray mBlockTextures;
};