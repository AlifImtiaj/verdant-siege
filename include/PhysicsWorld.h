#pragma once
#include "SFML/Graphics.hpp"
#include "RigidBody.h"
#include <vector>

class PhysicsWorld {
private:
    static constexpr float GRAVITY = 800.f;
    std::vector<RigidBody*> _rigidBodies;
    Collider _groundCollider;

public:
    void AddRigidBody(RigidBody* rb);
    void ClearRigidBody();

    void SetCollider(Collider collider) { _groundCollider = collider; }
    void Update(const float& deltaTime);

private:
    void ApplyGravity(RigidBody* rb, const float& deltaTime);
    void ResolveCollision(RigidBody* rb);
    bool CheckCollision(RigidBody* rb);
};