#include "Renderer.hpp"

const Vertex SELECT_BOX[] = {
    { { -0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.250000f, 0.656250f, 0.0f } },
    { {  0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.492188f, 0.656250f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.250000f, 0.333333f, 0.0f } },

    { {  0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.492188f, 0.656250f, 0.0f } },
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.492188f, 0.333333f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f, -0.000000f, -1.000000f },*/ { 0.250000f, 0.333333f, 0.0f } },


    { { -0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 1.000000f, 0.333400f, 0.0f } },
    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 0.750000f, 0.333400f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 1.000000f, 0.666600f, 0.0f } },

    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 0.750000f, 0.333400f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 0.750000f, 0.666600f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f,  0.000000f,  1.000000f },*/ { 1.000000f, 0.666600f, 0.0f } },


    { {  0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.492188f, 0.322917f, 0.0f } },
    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.492188f, 0.000000f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.250000f, 0.322917f, 0.0f } },

    { {  0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.492188f, 0.000000f, 0.0f } },
    { { -0.500000f,  0.500000f,  0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.250000f, 0.000000f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{  0.000000f,  1.000000f, -0.000000f },*/ { 0.250000f, 0.322917f, 0.0f } },


    { {  0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.500000f, 0.666600f, 0.0f } },
    { { -0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.250100f, 0.666600f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.500000f, 1.000000f, 0.0f } },

    { { -0.500000f, -0.500000f, -0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.250100f, 0.666600f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.250000f, 1.000000f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  0.000000f, -1.000000f, -0.000000f },*/ { 0.500000f, 1.000000f, 0.0f } },


    { { -0.500000f, -0.500000f, -0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.250000f, 0.666600f, 0.0f } },
    { { -0.500000f,  0.500000f, -0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.250000f, 0.333400f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.000000f, 0.666600f, 0.0f } },

    { { -0.500000f,  0.500000f, -0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.250000f, 0.333400f, 0.0f } },
    { { -0.500000f,  0.500000f,  0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.000000f, 0.333400f, 0.0f } },
    { { -0.500000f, -0.500000f,  0.500000f }, /*{ -1.000000f, -0.000000f,  0.000000f },*/ { 0.000000f, 0.666600f, 0.0f } },


    { {  0.500000f, -0.500000f, -0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.500000f, 0.656250f, 0.0f } },
    { {  0.500000f, -0.500000f,  0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.742188f, 0.656250f, 0.0f } },
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.500000f, 0.337333f, 0.0f } },

    { {  0.500000f, -0.500000f,  0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.742188f, 0.656250f, 0.0f } },
    { {  0.500000f,  0.500000f,  0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.742188f, 0.337333f, 0.0f } },
    { {  0.500000f,  0.500000f, -0.500000f }, /*{  1.000000f, -0.000000f, -0.000000f },*/ { 0.500000f, 0.337333f, 0.0f } },
};

Renderer::Renderer(hd::RenderContext &renderContext, BlockManager &blockMgr) : mRenderContext(renderContext), mBlockMgr(blockMgr) {
    std::vector<hd::VertexElement> attribs = {
        hd::VertexElement(hd::VertexElementType::Float3, 0, 0, sizeof(float)*0, false, false),
        //hd::VertexElement(hd::VertexElementType::Float3, 1, 0, sizeof(float)*3, false, false),
        hd::VertexElement(hd::VertexElementType::Float3, 2, 0, sizeof(float)*3, false, false)
    };
    mVertexFormat = mRenderContext.createVertexFormat(attribs);
    mSamplerState = mRenderContext.createSamplerState(hd::SamplerFilter::Point);

    mBlockProgram = mRenderContext.createProgramFromFile("data/shaders/block.glsl");
    mBlockProgramProjMatId = mRenderContext.getProgramConstantID(mBlockProgram, "gProjMat");
    mBlockProgramViewMatId = mRenderContext.getProgramConstantID(mBlockProgram, "gViewMat");

    mSelectBoxProgram = mRenderContext.createProgramFromFile("data/shaders/selectBox.glsl");
    mSelectBoxProgramProjMatId = mRenderContext.getProgramConstantID(mSelectBoxProgram, "gProjMat");
    mSelectBoxProgramViewMatId = mRenderContext.getProgramConstantID(mSelectBoxProgram, "gViewMat");
    mSelectBoxProgramWorldMatId = mRenderContext.getProgramConstantID(mSelectBoxProgram, "gWorldMat");
    mSelectBoxVertexBuffer = mRenderContext.createVertexBuffer(SELECT_BOX, sizeof(SELECT_BOX), hd::BufferUsage::Static);
}

Renderer::~Renderer() {
    mRenderContext.destroyVertexBuffer(mSelectBoxVertexBuffer);
    mRenderContext.destroyProgram(mSelectBoxProgram);
    mRenderContext.destroyProgram(mBlockProgram);
    mRenderContext.destroySamplerState(mSamplerState);
    mRenderContext.destroyVertexFormat(mVertexFormat);
}

void Renderer::onResize(int w, int h) {
    mRenderContext.setViewport(0, 0, w, h);
    mProjMat = glm::perspectiveFovLH(glm::pi<float>() / 4.0f, static_cast<float>(w), static_cast<float>(h), 0.01f, 1000.0f);
}

void Renderer::onDraw(const Scene &scene, const glm::mat4 &viewMat) {
    mRenderContext.setDepthState(true, hd::CompareFunc::Less, true);
    mRenderContext.bindVertexFormat(mVertexFormat);
    mRenderContext.bindSamplerState(mSamplerState, 0);
    mRenderContext.bindTexture2DArray(mBlockMgr.getTextureArray(), 0);

    mRenderContext.setRasterizerState(hd::CullFace::Back, hd::FillMode::Solid, hd::FrontFace::CCW, hd::PolygonOffset());
    mRenderContext.bindProgram(mBlockProgram);
    mRenderContext.setProgramConstant(mBlockProgramProjMatId, mProjMat);
    mRenderContext.setProgramConstant(mBlockProgramViewMatId, viewMat);
    for (const auto &chunk : scene.getChunks()) {
        mRenderContext.bindVertexBuffer(chunk->getVertexBuffer(), 0, 0, sizeof(Vertex));
        mRenderContext.draw(hd::PrimitiveType::Triangles, chunk->getVertexCount(), 0);
    }

    mRenderContext.setRasterizerState(hd::CullFace::Back, hd::FillMode::Wireframe, hd::FrontFace::CCW, hd::PolygonOffset());
    mRenderContext.bindProgram(mSelectBoxProgram);
    mRenderContext.setProgramConstant(mSelectBoxProgramProjMatId, mProjMat);
    mRenderContext.setProgramConstant(mSelectBoxProgramViewMatId, viewMat);
    glm::vec3 selectBoxPos = glm::vec3(0, 0, 0);
    glm::vec3 selectBoxSize = glm::vec3(1.001f, 1.001f, 1.001f);
    glm::mat4 worldMat = glm::translate(selectBoxPos)*glm::scale(selectBoxSize);
    mRenderContext.setProgramConstant(mSelectBoxProgramWorldMatId, worldMat);
    mRenderContext.bindVertexBuffer(mSelectBoxVertexBuffer, 0, 0, sizeof(Vertex));
    mRenderContext.draw(hd::PrimitiveType::Triangles, 36, 0);
}

const glm::mat4 &Renderer::getProjectionMatrix() const {
    return mProjMat;
}
