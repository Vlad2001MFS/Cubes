#include "Scene.hpp"
#include <algorithm>

Scene::Scene(hd::Window &window, hd::RenderContext &renderContext, BlockManager &blockMgr) : mWindow(window), mRenderContext(renderContext), mBlockMgr(blockMgr), mPlayer(*this, window) {
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

Chunk *Scene::findChunkByPosition(const glm::ivec3 &pos) const {
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    return it != mChunks.end() ? *it : nullptr;
}

void Scene::setBlock(BlockType type, const glm::ivec3 &pos) {
    glm::ivec3 chunkSize = glm::ivec3(Chunk::SIZE_X, Chunk::SIZE_Y, Chunk::SIZE_Z);
    glm::ivec3 chunkPos = pos / chunkSize;
    Chunk *chunk = findChunkByPosition(chunkPos);
    if (chunk) {
        glm::ivec3 blockPos = pos % chunkSize;
        chunk->setBlock(type, blockPos);
    }
    else {
        HD_LOG_WARNING("Failed to set block on position (%d %d %d) at chunk on position (%d %d %d). The chunk is not exists", pos.x, pos.y, pos.z, chunkPos.x, chunkPos.y, chunkPos.z);
    }
}

BlockType Scene::getBlock(const glm::ivec3 &pos) const {
    glm::ivec3 chunkSize = glm::ivec3(Chunk::SIZE_X, Chunk::SIZE_Y, Chunk::SIZE_Z);
    glm::ivec3 chunkPos = pos / chunkSize;
    Chunk *chunk = findChunkByPosition(chunkPos);
    if (chunk) {
        glm::ivec3 blockPos = pos % chunkSize;
        return chunk->getBlock(blockPos);
    }
    else {
        HD_LOG_WARNING("Failed to get block on position (%d %d %d) from chunk on position (%d %d %d). The chunk is not exists", pos.x, pos.y, pos.z, chunkPos.x, chunkPos.y, chunkPos.z);
        return BlockType::Air;
    }
}

void Scene::onFixedUpdate() {
    mPlayer.onFixedUpdate();
    for (auto &chunk : mChunks) {
        chunk->updateVertexBuffer();
    }
}

const Player &Scene::getPlayer() const {
    return mPlayer;
}

const std::vector<Chunk*> &Scene::getChunks() const {
    return mChunks;
}
