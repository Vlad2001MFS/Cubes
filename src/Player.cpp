#include "Player.hpp"

Player::Player(hd::Window &window) : mWindow(window) {
}

Player::~Player() {
}

void Player::onFixedUpdate() {
    auto speed = 1.0f;
    if (mWindow.isKeyDown(hd::KeyCode::W)) {
        mCamera.translate(0.0f, 0.0f, speed);
    }
    if (mWindow.isKeyDown(hd::KeyCode::S)) {
        mCamera.translate(0.0f, 0.0f, -speed);
    }
    if (mWindow.isKeyDown(hd::KeyCode::A)) {
        mCamera.translate(-speed, 0.0f, 0.0f);
    }
    if (mWindow.isKeyDown(hd::KeyCode::D)) {
        mCamera.translate(speed, 0.0f, 0.0f);
    }

    if (!mWindow.isKeyDown(hd::KeyCode::LControl)) {
        speed = 0.2f;
        auto deltaX = mWindow.getCenterX() - mWindow.getCursorPositionX();
        auto deltaY = mWindow.getCenterY() - mWindow.getCursorPositionY();
        mCamera.rotate(glm::radians(speed*deltaY), glm::radians(speed*deltaX), 0.0f);
        mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());
    }

    speed = 0.1f;
    if (mWindow.isKeyDown(hd::KeyCode::Up)) {
        mCamera.rotate(speed, 0.0f, 0.0f);
    }
    if (mWindow.isKeyDown(hd::KeyCode::Down)) {
        mCamera.rotate(-speed, 0.0f, 0.0f);
    }
    if (mWindow.isKeyDown(hd::KeyCode::Left)) {
        mCamera.rotate(0.0f, -speed, 0.0f);
    }
    if (mWindow.isKeyDown(hd::KeyCode::Right)) {
        mCamera.rotate(0.0f, speed, 0.0f);
    }
}

glm::mat4 Player::getViewMatrix() const {
    return mCamera.getViewMatrixLH();
}
