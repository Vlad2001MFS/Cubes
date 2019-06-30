#pragma once
#include "hd/Math/hdFirstPersonCamera.hpp"
#include "hd/System/hdWindow.hpp"

class Scene;

class Player {
public:
    Player(Scene &scene, hd::Window &window);
    ~Player();

    void onFixedUpdate();

    glm::ivec3 getSelectedBlockPosition() const;
    glm::vec3 getDirection() const;
    glm::mat4 getViewMatrix() const;

private:
    void mProcessMove();
    void mProcessLook();

    Scene &mScene;
    hd::Window &mWindow;
    hd::FirstPersonCamera mCamera;
    float mMoveSpeed;
    float mLookSpeed;
};