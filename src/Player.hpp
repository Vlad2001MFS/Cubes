#pragma once
#include "RaycastInfo.hpp"
#include "hd/Math/hdFirstPersonCamera.hpp"
#include "hd/IO/hdSerializer.hpp"
#include "hd/IO/hdDeserializer.hpp"
#include "hd/System/hdWindow.hpp"

class Scene;

class Player {
public:
    Player(Scene &scene, hd::Window &window);
    ~Player();

    void onFixedUpdate(const glm::mat4 &projMat);

    void save(hd::Serializer &stream);
    void load(hd::Deserializer &stream);
    
    void setPosition(const glm::vec3 &pos);

    glm::vec3 getDirection() const;
    glm::mat4 getViewMatrix() const;
    bool hasSelectedBlock() const;
    const RaycastInfo &getSelectedBlockRaycastInfo() const;
    const glm::vec3 &getPosition() const;

private:
    void mProcessMove();
    void mProcessLook();
    void mProcessSelectBlock(const glm::mat4 &projMat);
    void mProcessEditMap();

    Scene &mScene;
    hd::Window &mWindow;
    hd::FirstPersonCamera mCamera;
    float mMoveSpeed;
    float mLookSpeed;
    RaycastInfo mSelectedBlockRaycast;
    bool mHasSelectedBlock;
};