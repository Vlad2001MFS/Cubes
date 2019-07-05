#pragma once
#include "BlockManager.hpp"
#include "hd/IO/hdSerializer.hpp"
#include "hd/IO/hdDeserializer.hpp"
#include "3rd/include/glm/glm.hpp"

struct Vertex {
    Vertex(const glm::vec3 &pos, const glm::vec3 &texCoord);
    Vertex(float x, float y, float z, float tx, float ty, float tz);

    glm::vec3 pos;
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
    void save(hd::Serializer &stream);
    void load(hd::Deserializer &stream);

    void setBlock(BlockType type, const glm::ivec3 &pos);
    BlockType getBlock(const glm::ivec3 &pos) const;
    const hd::HVertexBuffer &getVertexBuffer() const;
    uint32_t getVertexCount() const;
    glm::ivec3 getGlobalBlockPosition(const glm::ivec3 &pos) const;
    const glm::ivec3 &getPosition() const;

private:
    bool mHasBlock(size_t x, size_t y, size_t z);
    uint32_t mCalcVertexCount();
    void mAddFace(Vertex *&vertexData, const Vertex *verts, size_t x, size_t y, size_t z, int texId);

    hd::RenderContext &mRenderContext;
    BlockType mBlocks[SIZE_X][SIZE_Y][SIZE_Z];
    glm::ivec3 mPos;
    hd::HVertexBuffer mVertexBuffer;
    uint32_t mVertexCount;
    bool mIsDirty;
};