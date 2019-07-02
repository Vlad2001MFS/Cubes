#include "Chunk.hpp"

const Vertex CUBE_FRONT[6] = {
    { { -0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.250000f, 0.656250f, 0.0f } },
    { {  0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.492188f, 0.656250f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.250000f, 0.333333f, 0.0f } },

    { {  0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.492188f, 0.656250f, 0.0f } },
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.492188f, 0.333333f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.250000f, 0.333333f, 0.0f } },
};                                                                                    

const Vertex CUBE_BACK[6] = {                                                         
    { { -0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 1.000000f, 0.333400f, 0.0f } },
    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 0.750000f, 0.333400f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 1.000000f, 0.666600f, 0.0f } },

    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 0.750000f, 0.333400f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 0.750000f, 0.666600f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 1.000000f, 0.666600f, 0.0f } },
};                                                                                    

const Vertex CUBE_UP[6] = {                                                           
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.492188f, 0.322917f, 0.0f } },
    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.492188f, 0.000000f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.250000f, 0.322917f, 0.0f } },

    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.492188f, 0.000000f, 0.0f } },
    { { -0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.250000f, 0.000000f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.250000f, 0.322917f, 0.0f } },
};                                                                                    

const Vertex CUBE_DOWN[6] = {                                                         
    { {  0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.500000f, 0.666600f, 0.0f } },
    { { -0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.250100f, 0.666600f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.500000f, 1.000000f, 0.0f } },

    { { -0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.250100f, 0.666600f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.250000f, 1.000000f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.500000f, 1.000000f, 0.0f } },
};                                                                                    

const Vertex CUBE_LEFT[6] = {                                                         
    { { -0.500000f, -0.500000f, -0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.250000f, 0.666600f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.250000f, 0.333400f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.000000f, 0.666600f, 0.0f } },

    { { -0.500000f,  0.500000f, -0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.250000f, 0.333400f, 0.0f } },
    { { -0.500000f,  0.500000f,  0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.000000f, 0.333400f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.000000f, 0.666600f, 0.0f } },
};                                                                                    

const Vertex CUBE_RIGHT[6] = {                                                        
    { {  0.500000f, -0.500000f, -0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.500000f, 0.656250f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.742188f, 0.656250f, 0.0f } },
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.500000f, 0.337333f, 0.0f } },

    { {  0.500000f, -0.500000f,  0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.742188f, 0.656250f, 0.0f } },
    { {  0.500000f,  0.500000f,  0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.742188f, 0.337333f, 0.0f } },
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.500000f, 0.337333f, 0.0f } },
};

Vertex::Vertex(const glm::vec3 &pos, const glm::vec3 &texCoord) : pos(pos), texCoord(texCoord) {
}

Vertex::Vertex(float x, float y, float z, float tx, float ty, float tz) : pos(x, y, z), texCoord(tx, ty, tz) {
}

Chunk::Chunk(hd::RenderContext &renderContext, const glm::ivec3 &pos) : mRenderContext(renderContext), mPos(pos) {
    mVertexBuffer = renderContext.createVertexBuffer(nullptr, sizeof(Vertex)*36, hd::BufferUsage::Static);
    mVertexCount = 0;
    mIsDirty = true;
}

Chunk::~Chunk() {
    mRenderContext.destroyVertexBuffer(mVertexBuffer);
}

void Chunk::updateVertexBuffer() {
    if (mIsDirty) {
        mIsDirty = false;
        mVertexCount = 0;
        auto hasBlock = [&](size_t x, size_t y, size_t z) {
            return x < SIZE_X && y < SIZE_Y && z < SIZE_Z && mBlocks[x][y][z] != BlockType::Air;
        };
        for (size_t z = 0; z < SIZE_Z; z++) {
            for (size_t y = 0; y < SIZE_Y; y++) {
                for (size_t x = 0; x < SIZE_X; x++) {
                    if (mBlocks[x][y][z] != BlockType::Air) {
                        if (!hasBlock(x, y, z - 1)) {
                            mVertexCount += 6;
                        }
                        if (!hasBlock(x, y, z + 1)) {
                            mVertexCount += 6;
                        }
                        if (!hasBlock(x, y + 1, z)) {
                            mVertexCount += 6;
                        }
                        if (!hasBlock(x, y - 1, z)) {
                            mVertexCount += 6;
                        }
                        if (!hasBlock(x - 1, y, z)) {
                            mVertexCount += 6;
                        }
                        if (!hasBlock(x + 1, y, z)) {
                            mVertexCount += 6;
                        }
                    }
                }
            }
        }
        mRenderContext.setVertexBufferData(mVertexBuffer, nullptr, sizeof(Vertex)*mVertexCount);
        Vertex *vertexData = static_cast<Vertex*>(mRenderContext.mapVertexBuffer(mVertexBuffer, hd::BufferAccess::Write));
        auto addFace = [&](const Vertex *verts, size_t x, size_t y, size_t z, int texId) {
            for (size_t i = 0; i < 6; i++) {
                const Vertex &v = verts[i];
                Vertex &vertex = *vertexData++;
                vertex.pos.x = v.pos.x + x + mPos.x*SIZE_X;
                vertex.pos.y = v.pos.y + y + mPos.y*SIZE_Y;
                vertex.pos.z = v.pos.z + z + mPos.z*SIZE_Z;
                vertex.texCoord.x = v.texCoord.x;
                vertex.texCoord.y = v.texCoord.y;
                vertex.texCoord.z = static_cast<float>(texId);
            }
        };
        for (size_t z = 0; z < SIZE_Z; z++) {
            for (size_t y = 0; y < SIZE_Y; y++) {
                for (size_t x = 0; x < SIZE_X; x++) {
                    BlockType block = mBlocks[x][y][z];
                    if (block != BlockType::Air) {
                        int texId = static_cast<int>(block) - 1;
                        if (!hasBlock(x, y, z - 1)) {
                            addFace(CUBE_FRONT, x, y, z, texId);
                        }
                        if (!hasBlock(x, y, z + 1)) {
                            addFace(CUBE_BACK, x, y, z, texId);
                        }
                        if (!hasBlock(x, y + 1, z)) {
                            addFace(CUBE_UP, x, y, z, texId);
                        }
                        if (!hasBlock(x, y - 1, z)) {
                            addFace(CUBE_DOWN, x, y, z, texId);
                        }
                        if (!hasBlock(x - 1, y, z)) {
                            addFace(CUBE_LEFT, x, y, z, texId);
                        }
                        if (!hasBlock(x + 1, y, z)) {
                            addFace(CUBE_RIGHT, x, y, z, texId);
                        }
                    }
                }
            }
        }
        mRenderContext.unmapVertexBuffer(mVertexBuffer);
    }
}

void Chunk::setBlock(BlockType type, const glm::ivec3 &pos) {
    if (glm::abs(pos.x) < SIZE_X && glm::abs(pos.y) < SIZE_Y && glm::abs(pos.z) < SIZE_Z) {
        int x = pos.x >= 0 ? pos.x : (SIZE_X + pos.x);
        int y = pos.y >= 0 ? pos.y : (SIZE_Y + pos.y);
        int z = pos.z >= 0 ? pos.z : (SIZE_Z + pos.z);
        BlockType &block = mBlocks[x][y][z];
        if (block != type) {
            block = type;
            mIsDirty = true;
        }
    }
}

BlockType Chunk::getBlock(const glm::ivec3 &pos) const {
    if (glm::abs(pos.x) < SIZE_X && glm::abs(pos.y) < SIZE_Y && glm::abs(pos.z) < SIZE_Z) {
        int x = pos.x >= 0 ? pos.x : (SIZE_X + pos.x);
        int y = pos.y >= 0 ? pos.y : (SIZE_Y + pos.y);
        int z = pos.z >= 0 ? pos.z : (SIZE_Z + pos.z);
        return mBlocks[x][y][z];
    }
    else {
        return BlockType::Air;
    }
}

const hd::HVertexBuffer &Chunk::getVertexBuffer() const {
    return mVertexBuffer;
}

uint32_t Chunk::getVertexCount() const {
    return mVertexCount;
}

const glm::ivec3 &Chunk::getPosition() const {
    return mPos;
}
