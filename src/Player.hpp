#pragma once
#include "hd/Math/hdFirstPersonCamera.hpp"
#include "hd/System/hdWindow.hpp"

class Player {
public:
    Player(hd::Window &window);
    ~Player();

    void onFixedUpdate();

    glm::mat4 getViewMatrix() const;

private:
    hd::Window &mWindow;
    hd::FirstPersonCamera mCamera;
};