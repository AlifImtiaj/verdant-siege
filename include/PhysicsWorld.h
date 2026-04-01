#pragma once
#include <vector>

#include "SFML/Graphics.hpp"
#include "RigidBody.h"

class PhysicsWorld {
private:
    static constexpr float GRAVITY = 800.f;
    std::vector<RigidBody*> _rigidBodies;

public:
    void AddRigidBody(RigidBody* rb);

    void AddRigidBody(std::vector<RigidBody>& rb);

    void ClearRigidBody();

    void Start();
    void Update(const float& deltaTime);

private:
    void ApplyGravity(RigidBody* rb, const float& deltaTime);
    void ResolveCollision(RigidBody* current, RigidBody* other);
    bool CheckCollision(RigidBody *current, RigidBody *other);
};