#include "BlockManager.hpp"

const std::vector<std::string> gBlockTexturePaths = {
    "data/textures/grass.png",
    "data/textures/dirt.png",
    "data/textures/stone.png"
};

BlockManager::BlockManager(hd::RenderContext &renderContext) : mRenderContext(renderContext) {
    mBlockTextures = mRenderContext.createTexture2DArrayFromFiles(gBlockTexturePaths);
}

BlockManager::~BlockManager() {
    mRenderContext.destroyTexture2DArray(mBlockTextures);
}

const hd::HTexture2DArray& BlockManager::getTextureArray() const {
    return mBlockTextures;
}
