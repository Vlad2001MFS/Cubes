#include "Player.hpp"
#include "Scene.hpp"

Player::Player(Scene &scene, hd::Window &window) : mScene(scene), mWindow(window) {
    mMoveSpeed = 1.0f;
    mLookSpeed = 0.2f;
}

Player::~Player() {
}

void Player::onFixedUpdate() {
    mProcessMove();
    mProcessLook();
}

glm::vec3 Player::getDirection() const {
    return mCamera.getDirectionLH();
}

glm::mat4 Player::getViewMatrix() const {
    return mCamera.getViewMatrixLH();
}

void Player::mProcessMove() {
    if (mWindow.isKeyDown(hd::KeyCode::W)) {
        mCamera.translate(0.0f, 0.0f, mMoveSpeed);
    }
    if (mWindow.isKeyDown(hd::KeyCode::S)) {
        mCamera.translate(0.0f, 0.0f, -mMoveSpeed);
    }
    if (mWindow.isKeyDown(hd::KeyCode::A)) {
        mCamera.translate(-mMoveSpeed, 0.0f, 0.0f);
    }
    if (mWindow.isKeyDown(hd::KeyCode::D)) {
        mCamera.translate(mMoveSpeed, 0.0f, 0.0f);
    }
}

void Player::mProcessLook() {
    if (!mWindow.isKeyDown(hd::KeyCode::LControl)) {
        auto deltaX = mWindow.getCenterX() - mWindow.getCursorPositionX();
        auto deltaY = mWindow.getCenterY() - mWindow.getCursorPositionY();
        mCamera.rotate(glm::radians(mLookSpeed*deltaY), glm::radians(mLookSpeed*deltaX), 0.0f);
        mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());
    }
}
