#pragma once
#include "Chunk.hpp"

class Scene {
public:
    Scene(hd::RenderContext &renderContext, BlockManager &blockMgr);
    ~Scene();

    Chunk *createChunk(const glm::ivec3 &pos);
    void destroyChunk(const glm::ivec3 &pos);

    void onFixedUpdate();

    const std::vector<Chunk*> &getChunks() const;

private:
    hd::RenderContext &mRenderContext;
    BlockManager &mBlockMgr;
    std::vector<Chunk*> mChunks;
};