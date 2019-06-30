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

    hd::HVertexFormat mVertexFormat;
    hd::HSamplerState mSamplerState;

    hd::HProgram mBlockProgram;
    hd::HProgramConstant mBlockProgramProjMatId;
    hd::HProgramConstant mBlockProgramViewMatId;

    hd::HProgram mSelectBoxProgram;
    hd::HProgramConstant mSelectBoxProgramProjMatId;
    hd::HProgramConstant mSelectBoxProgramViewMatId;
    hd::HProgramConstant mSelectBoxProgramWorldMatId;
    hd::HVertexBuffer mSelectBoxVertexBuffer;

    glm::mat4 mProjMat;
};