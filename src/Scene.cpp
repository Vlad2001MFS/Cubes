#include "Scene.hpp"
#include <algorithm>

Scene::Scene(hd::RenderContext &renderContext, BlockManager &blockMgr) : mRenderContext(renderContext), mBlockMgr(blockMgr) {
}

Scene::~Scene() {
    for (auto &chunk : mChunks) {
        HD_DELETE(chunk);
    }
}

Chunk *Scene::createChunk(const glm::ivec3 &pos) {
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    if (it == mChunks.end()) {
        auto chunk = new Chunk(mRenderContext, pos);
        mChunks.push_back(chunk);
        return chunk;
    }
    else {
        return *it;
    }
}

void Scene::destroyChunk(const glm::ivec3 &pos) {
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    if (it != mChunks.end()) {
        auto ptr = *it;
        mChunks.erase(std::remove(mChunks.begin(), mChunks.end(), *it), mChunks.end());
        HD_DELETE(ptr);
    }
}

void Scene::onFixedUpdate() {
    for (auto &chunk : mChunks) {
        chunk->updateVertexBuffer();
    }
}

const std::vector<Chunk*> &Scene::getChunks() const {
    return mChunks;
}
