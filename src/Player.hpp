#pragma once
#include "hd/Math/hdFirstPersonCamera.hpp"
#include "hd/System/hdWindow.hpp"

class Scene;

class Player {
public:
    Player(Scene &scene, hd::Window &window);
    ~Player();

    void onFixedUpdate();

    glm::vec3 getDirection() const;
    glm::mat4 getViewMatrix() const;

private:
    Scene &mScene;
    hd::Window &mWindow;
    hd::FirstPersonCamera mCamera;
};