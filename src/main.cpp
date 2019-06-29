#include "hd/Core/hdCommon.hpp"
#include "hd/Core/hdStringUtils.hpp"
#include "hd/IO/hdConfig.hpp"
#include "hd/IO/hdImage.hpp"
#include "hd/Math/hdFirstPersonCamera.h"
#include "hd/System/hdBaseApp.hpp"
#include "hd/Graphics/hdRenderContext.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

class Game : public hd::BaseApp {
public:
    void onInitialize() {
        mWindow.create("Cubes", 640, 480, hd::WindowFlags::Resizable, hd::OpenGLContextSettings());
        mContext.create(mWindow);

        mCam.setPosition(0.0f, 0.0f, -2.5f);

        mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());

        mBlockMgr = std::make_unique<BlockManager>(mContext);
        mScene = std::make_unique<Scene>(mContext, *mBlockMgr);
        mRenderer = std::make_unique<Renderer>(mContext, *mBlockMgr);

        for (int cz = 0; cz < 10; cz++) {
            for (int cx = 0; cx < 10; cx++) {
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
    }

    void onFixedUpdate() {
        mWindow.setTitle(hd::StringUtils::format("Cubes | FPS: %d | FrameTime: %f", getFps(), getFrameTime()));

        auto speed = 1.0f;
        if (mWindow.isKeyDown(hd::KeyCode::W)) {
            mCam.translate(0.0f, 0.0f, speed);
        }
        if (mWindow.isKeyDown(hd::KeyCode::S)) {
            mCam.translate(0.0f, 0.0f, -speed);
        }
        if (mWindow.isKeyDown(hd::KeyCode::A)) {
            mCam.translate(-speed, 0.0f, 0.0f);
        }
        if (mWindow.isKeyDown(hd::KeyCode::D)) {
            mCam.translate(speed, 0.0f, 0.0f);
        }

        if (!mWindow.isKeyDown(hd::KeyCode::LControl)) {
            speed = 0.2f;
            auto deltaX = mWindow.getCenterX() - mWindow.getCursorPositionX();
            auto deltaY = mWindow.getCenterY() - mWindow.getCursorPositionY();
            mCam.rotate(glm::radians(speed*deltaY), glm::radians(speed*deltaX), 0.0f);
            mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());
        }

        speed = 0.1f;
        if (mWindow.isKeyDown(hd::KeyCode::Up)) {
            mCam.rotate(speed, 0.0f, 0.0f);
        }
        if (mWindow.isKeyDown(hd::KeyCode::Down)) {
            mCam.rotate(-speed, 0.0f, 0.0f);
        }
        if (mWindow.isKeyDown(hd::KeyCode::Left)) {
            mCam.rotate(0.0f, -speed, 0.0f);
        }
        if (mWindow.isKeyDown(hd::KeyCode::Right)) {
            mCam.rotate(0.0f, speed, 0.0f);
        }

        mScene->onFixedUpdate();
    }

    void onDraw() {
        mContext.clearRenderTarget(0.5f, 0.5f, 1.0f, 1.0f);
        mContext.clearDepthStencil(1.0f);

        mRenderer->onDraw(*mScene, mCam.getViewMatrixLH());

        mWindow.swapBuffers();
    }

private:
    hd::RenderContext mContext;
    std::unique_ptr<BlockManager> mBlockMgr;
    std::unique_ptr<Scene> mScene;
    std::unique_ptr<Renderer> mRenderer;
    hd::FirstPersonCamera mCam;
};

HD_APP_MAIN(Game)