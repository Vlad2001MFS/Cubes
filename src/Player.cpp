#include "Player.hpp"
#include "Scene.hpp"

Player::Player(Scene &scene, hd::Window &window) : mScene(scene), mWindow(window) {
    mMoveSpeed = 0.1f;
    mLookSpeed = 0.2f;
    mHasSelectedBlock = false;
}

Player::~Player() {
}

void Player::onFixedUpdate(const glm::mat4 &projMat) {
    mProcessMove();
    mProcessLook();
    mProcessSelectBlock(projMat);
    mProcessEditMap();
}

void Player::setPosition(const glm::vec3& pos) {
    mCamera.setPosition(pos);
}

glm::vec3 Player::getDirection() const {
    return mCamera.getDirectionLH();
}

glm::mat4 Player::getViewMatrix() const {
    return mCamera.getViewMatrixLH();
}

bool Player::hasSelectedBlock() const {
    return mHasSelectedBlock;
}

const RaycastInfo &Player::getSelectedBlockRaycastInfo() const {
    return mSelectedBlockRaycast;
}

const glm::vec3 &Player::getPosition() const {
    return mCamera.getPosition();
}

void Player::mProcessMove() {
    float mult = mWindow.isKeyDown(hd::KeyCode::LShift) ? 10.0f : 1.0f;
    if (mWindow.isKeyDown(hd::KeyCode::W)) {
        mCamera.translate(0.0f, 0.0f, mMoveSpeed*mult);
    }
    if (mWindow.isKeyDown(hd::KeyCode::S)) {
        mCamera.translate(0.0f, 0.0f, -mMoveSpeed*mult);
    }
    if (mWindow.isKeyDown(hd::KeyCode::A)) {
        mCamera.translate(-mMoveSpeed*mult, 0.0f, 0.0f);
    }
    if (mWindow.isKeyDown(hd::KeyCode::D)) {
        mCamera.translate(mMoveSpeed*mult, 0.0f, 0.0f);
    }
}

void Player::mProcessLook() {
    if (!mWindow.isKeyDown(hd::KeyCode::LControl)) {
        int deltaX = mWindow.getCenterX() - mWindow.getCursorPositionX();
        int deltaY = mWindow.getCenterY() - mWindow.getCursorPositionY();
        mCamera.rotate(glm::radians(mLookSpeed*deltaY), glm::radians(mLookSpeed*deltaX), 0.0f);
        mWindow.setCursorPosition(mWindow.getCenterX(), mWindow.getCenterY());
    }
}

void Player::mProcessSelectBlock(const glm::mat4 &projMat) {
    glm::vec4 viewport = glm::vec4(0, 0, mWindow.getSizeX(), mWindow.getSizeY());
    glm::vec2 center = glm::vec2(mWindow.getCenterX(), mWindow.getCenterY());
    glm::vec3 rayBegin = glm::unProject(glm::vec3(center, -1), getViewMatrix(), projMat, viewport);
    glm::vec3 rayEnd = glm::unProject(glm::vec3(center, 1), getViewMatrix(), projMat, viewport);
    hd::Ray ray(rayBegin, glm::normalize(rayEnd - rayBegin));
    std::vector<RaycastInfo> intersections = mScene.raycast(ray, 10);
    if (!intersections.empty()) {
        mSelectedBlockRaycast = intersections.front();
        for (size_t i = 1; i < intersections.size(); i++) {
            if (intersections[i].blockType != BlockType::Air && glm::abs(intersections[i].intersection.dist) < glm::abs(mSelectedBlockRaycast.intersection.dist)) {
                mSelectedBlockRaycast = intersections[i];
            }
        }
    }
    mHasSelectedBlock = !intersections.empty() && mSelectedBlockRaycast.intersection.hasIntersection && mSelectedBlockRaycast.blockType != BlockType::Air;
}

void Player::mProcessEditMap() {
    static bool isLBMPressed = false;
    if (!isLBMPressed && mWindow.isMouseButtonDown(hd::MouseButton::Left)) {
        isLBMPressed = true;
        if (getSelectedBlockRaycastInfo().intersection.hasIntersection) {
            mScene.setBlock(BlockType::Air, getSelectedBlockRaycastInfo().blockPos);
        }
    }
    if (!mWindow.isMouseButtonDown(hd::MouseButton::Left)) {
        isLBMPressed = false;
    }

    static BlockType buildBlock = BlockType::Dirt;
    if (mWindow.isKeyDown(hd::KeyCode::Num1)) {
        buildBlock = BlockType::Dirt;
    }
    if (mWindow.isKeyDown(hd::KeyCode::Num2)) {
        buildBlock = BlockType::Grass;
    }
    if (mWindow.isKeyDown(hd::KeyCode::Num3)) {
        buildBlock = BlockType::Stone;
    }

    static bool isRBMPressed = false;
    if (!isRBMPressed && mWindow.isMouseButtonDown(hd::MouseButton::Right)) {
        isRBMPressed = true;
        if (getSelectedBlockRaycastInfo().intersection.hasIntersection) {
            glm::vec3 blockPos = getSelectedBlockRaycastInfo().blockPos;
            glm::vec3 intersectionPoint = getSelectedBlockRaycastInfo().intersection.point;
            glm::vec3 newBlockPos = blockPos + glm::round(intersectionPoint - blockPos);
            mScene.setBlock(buildBlock, newBlockPos);
        }
    }
    if (!mWindow.isMouseButtonDown(hd::MouseButton::Right)) {
        isRBMPressed = false;
    }
}
