#include "Renderer.hpp"

Renderer::Renderer(hd::RenderContext &renderContext, BlockManager &blockMgr) : mRenderContext(renderContext), mBlockMgr(blockMgr) {
    mSimpleProgram = mRenderContext.createProgramFromFile("data/shaders/simple.glsl");
    mSimpleProgramProjId = mRenderContext.getProgramConstantID(mSimpleProgram, "gProjMat");
    mSimpleProgramViewId = mRenderContext.getProgramConstantID(mSimpleProgram, "gViewMat");

    std::vector<hd::VertexElement> attribs = {
        hd::VertexElement(hd::VertexElementType::Float3, 0, 0, sizeof(float)*0, false, false),
        //hd::VertexElement(hd::VertexElementType::Float3, 1, 0, sizeof(float)*3, false, false),
        hd::VertexElement(hd::VertexElementType::Float3, 2, 0, sizeof(float)*3, false, false)
    };
    mVertexFormat = mRenderContext.createVertexFormat(attribs);
    
    mSamplerState = mRenderContext.createSamplerState(hd::SamplerFilter::Point);
}

Renderer::~Renderer() {
    mRenderContext.destroySamplerState(mSamplerState);
    mRenderContext.destroyVertexFormat(mVertexFormat);
    mRenderContext.destroyProgram(mSimpleProgram);
}

void Renderer::onResize(int w, int h) {
    mRenderContext.setViewport(0, 0, w, h);
    mProjMat = glm::perspectiveFovLH(glm::pi<float>() / 4.0f, static_cast<float>(w), static_cast<float>(h), 0.01f, 1000.0f);
}

void Renderer::onDraw(const Scene &scene, const glm::mat4 &viewMat) {
    mRenderContext.setDepthState(true, hd::CompareFunc::Less, true);
    mRenderContext.setRasterizerState(hd::CullFace::Back, hd::FillMode::Solid, hd::FrontFace::CCW, hd::PolygonOffset());
    mRenderContext.bindVertexFormat(mVertexFormat);
    mRenderContext.bindProgram(mSimpleProgram);
    mRenderContext.setProgramConstant(mSimpleProgramProjId, mProjMat);
    mRenderContext.setProgramConstant(mSimpleProgramViewId, viewMat);
    mRenderContext.bindSamplerState(mSamplerState, 0);

    mRenderContext.bindTexture2DArray(mBlockMgr.getTextureArray(), 0);
    for (const auto &chunk : scene.getChunks()) {
        mRenderContext.bindVertexBuffer(chunk->getVertexBuffer(), 0, 0, sizeof(Vertex));
        mRenderContext.draw(hd::PrimitiveType::Triangles, chunk->getVertexCount(), 0);
    }
}
