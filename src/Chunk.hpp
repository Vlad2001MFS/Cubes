#pragma once
#include "BlockManager.hpp"
#include "3rd/include/glm/glm.hpp"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 texCoord;
};

class Chunk {
public:
    static const int SIZE_X = 16;
    static const int SIZE_Y = 256;
    static const int SIZE_Z = 16;

    Chunk(hd::RenderContext &renderContext, const glm::ivec3 &pos);
    ~Chunk();

    void updateVertexBuffer();

    void setBlock(BlockType type, const glm::ivec3 &pos);
    BlockType getBlock(const glm::ivec3 &pos) const;
    const hd::HVertexBuffer &getVertexBuffer() const;
    size_t getVertexCount() const;
    const glm::ivec3 &getPosition() const;

private:
    hd::RenderContext &mRenderContext;
    BlockType mBlocks[SIZE_X][SIZE_Y][SIZE_Z];
    glm::ivec3 mPos;
    hd::HVertexBuffer mVertexBuffer;
    size_t mVertexCount;
    bool mIsDirty;
};