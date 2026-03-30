#include "PhysicsWorld.h"

void PhysicsWorld::AddRigidBody(RigidBody *rb) {
    _rigidBodies.emplace_back(rb);
}

void PhysicsWorld::ClearRigidBody() {
    _rigidBodies.clear();
}

void PhysicsWorld::Update(const float& deltaTime) {
    
    for (auto rb : _rigidBodies) {
        rb->Update();
        
        // if (rb->GetCollider().GetType() == ColliderType::DYNAMIC) {
        //     if (!rb->IsGrounded()) {
        //         ApplyGravity(rb, deltaTime);
        //     }
        // }
    }
}

void PhysicsWorld::ApplyGravity(RigidBody* rb, const float& deltaTime) {
        sf::Vector2f velocity = rb->GetVelocity();
        velocity.y += GRAVITY * rb->GetGravityScale() * deltaTime;
        rb->SetVelocity(velocity);
}

void PhysicsWorld::ResolveCollision(RigidBody *rb) {
    
}
