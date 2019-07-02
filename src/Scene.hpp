#pragma once
#include "Chunk.hpp"
#include "Player.hpp"
#include "RaycastInfo.hpp"
#include "hd/Math/hdMathUtils.hpp"

class Scene {
public:
    Scene(hd::Window &window, hd::RenderContext &renderContext, BlockManager &blockMgr);
    ~Scene();

    Chunk *createChunk(const glm::ivec3 &pos);
    void destroyChunk(const glm::ivec3 &pos);
    Chunk *findChunkByPosition(const glm::ivec3 &pos) const;

    void setBlock(BlockType type, const glm::ivec3 &pos);
    BlockType getBlock(const glm::ivec3 &pos) const;

    std::vector<RaycastInfo> raycast(const hd::Ray &ray, int raycastRadius) const;

    void onFixedUpdate(const glm::mat4 &projMat);

    const Player &getPlayer() const;
    const std::vector<Chunk*> &getChunks() const;

private:
    glm::ivec3 mGetChunkPos(const glm::ivec3 &pos) const;
    glm::ivec3 mGetBlockLocalPos(const glm::ivec3 &pos) const;

    hd::Window &mWindow;
    hd::RenderContext &mRenderContext;
    BlockManager &mBlockMgr;
    Player mPlayer;
    std::vector<Chunk*> mChunks;
};