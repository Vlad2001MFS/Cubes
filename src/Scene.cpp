#include "Scene.hpp"
#include <algorithm>

Scene::Scene(hd::Window &window, hd::RenderContext &renderContext, BlockManager &blockMgr) : mWindow(window), mRenderContext(renderContext), mBlockMgr(blockMgr), mPlayer(*this, window) {
    mPlayer.setPosition(glm::vec3(0.0f, 130.0f, 0.0f));
}

Scene::~Scene() {
    for (auto &chunk : mChunks) {
        HD_DELETE(chunk);
    }
}

Chunk *Scene::createChunk(const glm::ivec3 &pos) {
    HD_ASSERT(pos.y == 0);
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    if (it == mChunks.end()) {
        Chunk *chunk = new Chunk(mRenderContext, pos);
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
        Chunk *ptr = *it;
        mChunks.erase(std::remove(mChunks.begin(), mChunks.end(), *it), mChunks.end());
        HD_DELETE(ptr);
    }
}

Chunk *Scene::findChunkByPosition(const glm::ivec3 &pos) const {
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    return it != mChunks.end() ? *it : nullptr;
}

void Scene::setBlock(BlockType type, const glm::ivec3 &pos) {
    glm::ivec3 chunkPos = mGetChunkPos(pos);
    Chunk *chunk = findChunkByPosition(chunkPos);
    if (chunk) {
        chunk->setBlock(type, mGetBlockLocalPos(pos));
    }
}

BlockType Scene::getBlock(const glm::ivec3 &pos) const {
    glm::ivec3 chunkPos = mGetChunkPos(pos);
    Chunk *chunk = findChunkByPosition(chunkPos);
    if (chunk) {
        return chunk->getBlock(mGetBlockLocalPos(pos));
    }
    else {
        return BlockType::Air;
    }
}

std::vector<RaycastInfo> Scene::raycast(const hd::Ray& ray, int raycastRadius) const {
    std::vector<RaycastInfo> data;
    int xMin = glm::round(ray.getOrigin().x) - raycastRadius;
    int xMax = glm::round(ray.getOrigin().x) + raycastRadius;
    int yMin = glm::round(ray.getOrigin().y) - raycastRadius;
    int yMax = glm::round(ray.getOrigin().y) + raycastRadius;
    int zMin = glm::round(ray.getOrigin().z) - raycastRadius;
    int zMax = glm::round(ray.getOrigin().z) + raycastRadius;
    for (int z = zMin; z < zMax; z++) {
        for (int y = yMin; y < yMax; y++) {
            for (int x = xMin; x < xMax; x++) {
                RaycastInfo info;
                info.blockPos = glm::ivec3(x, y, z);
                info.intersection = ray.intersectAABB(hd::AABB(info.blockPos, glm::vec3(0.5f, 0.5f, 0.5f)));
                if (info.intersection.hasIntersection) {
                    info.blockType = getBlock(info.blockPos);
                    data.push_back(info);
                }
            }
        }
    }
    return data;
}

void Scene::onFixedUpdate(const glm::mat4 &projMat) {
    mPlayer.onFixedUpdate(projMat);
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

glm::ivec3 Scene::mGetChunkPos(const glm::ivec3& pos) const {
    glm::ivec3 result(0, 0, 0);
    glm::ivec3 p = pos;
    if (p.x < 0) {
        p.x += 1;
        result.x -= 1;
    }
    if (p.z < 0) {
        p.z += 1;
        result.z -= 1;
    }
    result.x += p.x / Chunk::SIZE_X;
    result.z += p.z / Chunk::SIZE_Z;
    return result;
}

glm::ivec3 Scene::mGetBlockLocalPos(const glm::ivec3& pos) const {
    glm::ivec3 chunkPos = mGetChunkPos(pos);
    return pos - chunkPos*glm::ivec3(Chunk::SIZE_X, 0, Chunk::SIZE_Z);
}
