#include "hd/Core/hdCommon.hpp"
#include "hd/Core/hdStringUtils.hpp"
#include "hd/IO/hdConfig.hpp"
#include "hd/IO/hdImage.hpp"
#include "hd/System/hdBaseApp.hpp"
#include "hd/Graphics/hdRenderContext.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

class Game : public hd::BaseApp {
public:
    void onInitialize() {
        mWindow.create("Cubes", 640, 480, hd::WindowFlags::Resizable, hd::OpenGLContextSettings());
        mContext.create(mWindow);

        mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());

        mBlockMgr = std::make_unique<BlockManager>(mContext);
        mScene = std::make_unique<Scene>(mWindow, mContext, *mBlockMgr);
        mRenderer = std::make_unique<Renderer>(mContext, *mBlockMgr);

        int halfSize = 1;
        for (int cz = -halfSize; cz <= halfSize; cz++) {
            for (int cx = -halfSize; cx <= halfSize; cx++) {
                auto chunk = mScene->createChunk(glm::ivec3(cx, 0, cz));
                for (size_t z = 0; z < 16; z++) {
                    for (size_t y = 0; y < 256; y++) {
                        for (size_t x = 0; x < 16; x++) {
                            if (y < 42) {
                                chunk->setBlock(BlockType::Stone, glm::ivec3(x, y, z));
                            }
                            else if (y < 84) {
                                chunk->setBlock(BlockType::Dirt, glm::ivec3(x, y, z));
                            }
                            else if (y < 128) {
                                chunk->setBlock(BlockType::Grass, glm::ivec3(x, y, z));
                            }
                            else {
                                chunk->setBlock(BlockType::Air, glm::ivec3(x, y, z));
                            }
                        }
                    }
                }
            }
        }
    }

    void onEvent(const hd::WindowEvent &event) {
        if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released && event.key.code == hd::KeyCode::Escape) {
            mWindow.close();
        }
        if (event.type == hd::WindowEventType::Resize) {
            mRenderer->onResize(event.resize.width, event.resize.height);
        }
        if (event.type == hd::WindowEventType::FocusGained || event.type == hd::WindowEventType::FocusLost) {
            mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());
        }
    }

    void onFixedUpdate() {
        mWindow.setTitle(hd::StringUtils::format("Cubes | FPS: %d | FrameTime: %f", getFps(), getFrameTime()));

        mScene->onFixedUpdate(mRenderer->getProjectionMatrix());
    }

    void onDraw() {
        mContext.clearRenderTarget(0.5f, 0.5f, 1.0f, 1.0f);
        mContext.clearDepthStencil(1.0f);

        mRenderer->onDraw(*mScene, mScene->getPlayer().getViewMatrix());

        mWindow.swapBuffers();
    }

private:
    hd::RenderContext mContext;
    std::unique_ptr<BlockManager> mBlockMgr;
    std::unique_ptr<Scene> mScene;
    std::unique_ptr<Renderer> mRenderer;
};

HD_APP_MAIN(Game)