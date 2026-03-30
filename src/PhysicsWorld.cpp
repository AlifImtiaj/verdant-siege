#include "PhysicsWorld.h"

void PhysicsWorld::AddRigidBody(RigidBody *rb) {
    _rigidBodies.emplace_back(rb);
}

void PhysicsWorld::ClearRigidBody() {
    _rigidBodies.clear();
}

void PhysicsWorld::Update(const float& deltaTime) {
    
    for (auto rb : _rigidBodies) {
        rb->SetGrounded(false); // need to fix why not jumping, later
        CheckCollision(rb);
        if (rb->GetCollider().GetType() == ColliderType::DYNAMIC) {
            if (!rb->IsGrounded()) {
                ApplyGravity(rb, deltaTime);
            }
        }
        rb->Update(deltaTime);
    }
}

void PhysicsWorld::ApplyGravity(RigidBody* rb, const float& deltaTime) {
        sf::Vector2f velocity = rb->GetVelocity();
        velocity.y += GRAVITY * rb->GetGravityScale() * deltaTime;
        rb->SetVelocity(velocity);
}

void PhysicsWorld::ResolveCollision(RigidBody *rb) {
    
}

bool PhysicsWorld::CheckCollision(RigidBody* rb) {
    sf::FloatRect bounds = rb->GetCollider().GetBounds();
    float groundY = _groundCollider.GetBounds().position.y;

    if (bounds.position.y + bounds.size.y >= groundY) {
        // player was falling down slowly.
        // to fix this, i had to set the position
        rb->SetPosition({bounds.position.x, groundY - bounds.size.y});
        sf::Vector2f vel = rb->GetVelocity();
        vel.y = 0.f;  
        rb->SetVelocity(vel);
        rb->SetGrounded(true);
        return true;
    }
    return false;
}
