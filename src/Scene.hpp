#pragma once
#include "Chunk.hpp"
#include "Player.hpp"
#include "RaycastInfo.hpp"
#include "hd/Math/hdMathUtils.hpp"

class Scene {
public:
    Scene(hd::Window &window, hd::RenderContext &renderContext, BlockManager &blockMgr);
    ~Scene();

    void clear();

    Chunk *createChunk(const glm::ivec3 &pos);
    void destroyChunk(const glm::ivec3 &pos);
    Chunk *findChunkByPosition(const glm::ivec3 &pos) const;

    void save(const std::string &name);
    void load(const std::string &name);

    void setBlock(BlockType type, const glm::ivec3 &pos);
    BlockType getBlock(const glm::ivec3 &pos) const;

    std::vector<RaycastInfo> raycast(const hd::Ray &ray, int raycastRadius) const;

    void onFixedUpdate(const glm::mat4 &projMat);

    const Player &getPlayer() const;
    const std::vector<Chunk*> &getChunks() const;

private:
    void mDestroyChunk(Chunk *chunk);
    glm::ivec3 mGetChunkPos(const glm::ivec3 &pos) const;
    glm::ivec3 mGetBlockLocalPos(const glm::ivec3 &pos) const;

    hd::Window &mWindow;
    hd::RenderContext &mRenderContext;
    BlockManager &mBlockMgr;
    Player mPlayer;
    std::vector<Chunk*> mChunks;
    int mViewDistance;
};