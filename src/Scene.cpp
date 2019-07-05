#include "Scene.hpp"
#include "hd/Core/hdStringUtils.hpp"
#include <algorithm>
#include <filesystem>

Scene::Scene(hd::Window &window, hd::RenderContext &renderContext, BlockManager &blockMgr) : mWindow(window), mRenderContext(renderContext), mBlockMgr(blockMgr), mPlayer(*this, window) {
    mPlayer.setPosition(glm::vec3(0.0f, 130.0f, 0.0f));
    mViewDistance = 5;
}

Scene::~Scene() {
    clear();
}

void Scene::clear() {
    for (auto &chunk : mChunks) {
        HD_DELETE(chunk);
    }
    mChunks.clear();
}

Chunk *Scene::createChunk(const glm::ivec3 &pos) {
    HD_ASSERT(pos.y == 0);
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    if (it == mChunks.end()) {
        Chunk *chunk = new Chunk(mRenderContext, pos);
        for (size_t z = 0; z < 16; z++) {
            for (size_t y = 0; y < 256; y++) {
                for (size_t x = 0; x < 16; x++) {
                    if (y < 42) {
                        chunk->setBlock(BlockType::Stone, glm::ivec3(x, y, z));
                    }
                    else if (y < 84) {
                        chunk->setBlock(BlockType::Dirt, glm::ivec3(x, y, z));
                    }
                    else if (y < 128) {
                        chunk->setBlock(BlockType::Grass, glm::ivec3(x, y, z));
                    }
                    else {
                        chunk->setBlock(BlockType::Air, glm::ivec3(x, y, z));
                    }
                }
            }
        }
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
        mDestroyChunk(*it);
    }
}

Chunk *Scene::findChunkByPosition(const glm::ivec3 &pos) const {
    auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition() == pos; });
    return it != mChunks.end() ? *it : nullptr;
}

void Scene::save(const std::string &name) {
    std::string worldsFolder = "data/worlds";
    if (!std::filesystem::exists(worldsFolder)) {
        std::filesystem::create_directory(worldsFolder);
    }
    std::string worldFolder = worldsFolder + "/" + name;
    if (std::filesystem::exists(worldFolder)) {
        std::filesystem::remove_all(worldFolder);
    }
    if (!std::filesystem::exists(worldFolder)) {
        std::filesystem::create_directory(worldFolder);
    }

    std::string worldMain = worldFolder + "/main.bin";
    hd::Serializer main(worldMain);
    mPlayer.save(main);
    main.write<uint64_t>(mChunks.size());

    for (uint64_t i = 0; i < mChunks.size(); i++) {
        std::string chunkFile = worldFolder + "/chunk_" + hd::StringUtils::fromUint64(i) + ".bin";
        hd::Serializer stream(chunkFile);
        mChunks[i]->save(stream);
    }
}

void Scene::load(const std::string &name) {
    clear();

    std::string worldFolder = "data/worlds/" + name;
    if (std::filesystem::exists(worldFolder)) {
        std::string worldMain = worldFolder + "/main.bin";
        hd::Deserializer main(worldMain);

        mPlayer.load(main);
        uint64_t chunksCount = main.read<uint64_t>();

        for (uint64_t i = 0; i < chunksCount; i++) {
            std::string chunkFile = worldFolder + "/chunk_" + hd::StringUtils::fromUint64(i) + ".bin";
            hd::Deserializer stream(chunkFile);
            createChunk(glm::ivec3(0, 0, i))->load(stream);
            HD_LOG_INFO("LOAD '%s'", chunkFile.data());
        }
    }
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

    glm::ivec3 currentChunkPos = mGetChunkPos(mPlayer.getPosition());
    int xMin = currentChunkPos.x - mViewDistance;
    int xMax = currentChunkPos.x + mViewDistance;
    int zMin = currentChunkPos.z - mViewDistance;
    int zMax = currentChunkPos.z + mViewDistance;
    bool isChunkCreated = false;
    for (int z = zMin; z <= zMax; z++) {
        for (int x = xMin; x <= xMax; x++) {
            if (!isChunkCreated) {
                auto it = std::find_if(mChunks.begin(), mChunks.end(), [&](const Chunk *chunk) { return chunk->getPosition().x == x && chunk->getPosition().z == z; });
                if (it == mChunks.end()) {
                    isChunkCreated = true;
                    createChunk(glm::ivec3(x, 0, z));
                }
            }
        }
    }

    for (auto &chunk : mChunks) {
        if (chunk->getPosition().x < xMin || chunk->getPosition().x > xMax || chunk->getPosition().z < zMin || chunk->getPosition().z > zMax) {
            mDestroyChunk(chunk);
            break;
        }
    }

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

void Scene::mDestroyChunk(Chunk *chunk) {
    mChunks.erase(std::remove(mChunks.begin(), mChunks.end(), chunk), mChunks.end());
    HD_DELETE(chunk);
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
