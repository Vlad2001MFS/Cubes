#pragma once
#include "Scene.hpp"

class Renderer {
public:
    Renderer(hd::RenderContext &renderContext, BlockManager &blockMgr);
    ~Renderer();

    void onResize(int w, int h);
    void onDraw(const Scene &scene, const glm::mat4 &viewMat);

private:
    hd::RenderContext &mRenderContext;
    BlockManager &mBlockMgr;
    hd::HProgram mSimpleProgram;
    hd::HProgramConstant mSimpleProgramProjId;
    hd::HProgramConstant mSimpleProgramViewId;
    hd::HVertexFormat mVertexFormat;
    hd::HSamplerState mSamplerState;
    glm::mat4 mProjMat;
};