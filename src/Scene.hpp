#pragma once
#include "Chunk.hpp"
#include "Player.hpp"

class Scene {
public:
    Scene(hd::Window &window, hd::RenderContext &renderContext, BlockManager &blockMgr);
    ~Scene();

    Chunk *createChunk(const glm::ivec3 &pos);
    void destroyChunk(const glm::ivec3 &pos);

    void onFixedUpdate();

    const Player &getPlayer() const;
    const std::vector<Chunk*> &getChunks() const;

private:
    hd::Window &mWindow;
    hd::RenderContext &mRenderContext;
    BlockManager &mBlockMgr;
    Player mPlayer;
    std::vector<Chunk*> mChunks;
};