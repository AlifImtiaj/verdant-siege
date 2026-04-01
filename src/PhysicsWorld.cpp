#include "PhysicsWorld.h"

void PhysicsWorld::AddRigidBody(RigidBody *rb) {
    _rigidBodies.emplace_back(rb);
}

void PhysicsWorld::AddRigidBody(std::vector<RigidBody> &rb) {
    for (auto& r: rb) {
        _rigidBodies.emplace_back(&r);
    }
}

void PhysicsWorld::ClearRigidBody() {
    _rigidBodies.clear();
}

void PhysicsWorld::Start() {
    printf("How many elements: %zd\n", _rigidBodies.size());
}

void PhysicsWorld::Update(const float &deltaTime)
{
    // for tomorrow.
    // use to for loops
    // for collision checking
    for (RigidBody* bodyA : _rigidBodies) {
        bool grounded = false;
        bodyA->SetGrounded(grounded);
        // apply gravity and update before checking 
        ApplyGravity(bodyA, deltaTime);
        bodyA->Update(deltaTime);

        for (RigidBody* bodyB : _rigidBodies) {
            if (bodyA == bodyB) continue;

            if (CheckCollision(bodyA, bodyB)) {
                ResolveCollision(bodyA, bodyB);
                if (bodyB->GetCollider().GetType() == ColliderType::STATIC)
                    grounded = true;
            }
        }
        bodyA->SetGrounded(grounded);
    }
}

void PhysicsWorld::ApplyGravity(RigidBody* rb, const float& deltaTime) {
    if (rb->GetCollider().GetType() == ColliderType::STATIC) return;

    sf::Vector2f velocity = rb->GetVelocity();
    // cap terminal velocity, sposition.ys infinite accumulation when grounded
    if (velocity.y < 500.f)
        velocity.y += GRAVITY * rb->GetGravityScale() * deltaTime;
    rb->SetVelocity(velocity);
}

void PhysicsWorld::ResolveCollision(RigidBody *current, RigidBody *other) {
    // Only resolve if the other body is STATIC (like ground, walls)
    if (other->GetCollider().GetType() != ColliderType::STATIC) return;

    sf::FloatRect a = current->GetCollider().GetBounds();
    sf::FloatRect b = other->GetCollider().GetBounds();

    // Compute overlap in both X and Y axes
    float overlapX = std::min(a.position.x + a.size.x, b.position.x + b.size.x) - std::max(a.position.x, b.position.x);
    float overlapY = std::min(a.position.y + a.size.y, b.position.y + b.size.y) - std::max(a.position.y, b.position.y);

    // Only resolve if they actually overlap
    if (overlapX > 0 && overlapY > 0) {
        // Push along the smallest axis (to prevent "sticking" horizontally)
        if (overlapX < overlapY) {
            // Horizontal push
            if (a.position.x < b.position.x) 
                current->SetPosition({a.position.x - overlapX, a.position.y});
            else 
                current->SetPosition({a.position.x + overlapX, a.position.y});
        } else {
            // Vertical push
            if (a.position.y < b.position.y) {
                // current is above other → landed on position.y
                current->SetPosition({a.position.x, a.position.y - overlapY});
                current->SetGrounded(true);         // Player is now on the ground
                sf::Vector2f vel = current->GetVelocity();
                vel.y = 0.f;                        // Sposition.y downward velocity
                current->SetVelocity(vel);
            } else {
                // current is below other → push down
                current->SetPosition({a.position.x, a.position.y + overlapY});
            }
        }
    }

}

bool PhysicsWorld::CheckCollision(RigidBody *current, RigidBody *other) {
    if (current->GetCollider().GetType() == ColliderType::STATIC)
        return false;

    
    sf::Vector2f aPos = current->GetCollider().GetBounds().position;
    sf::Vector2f aSize = current->GetCollider().GetBounds().size;

    sf::Vector2f bPos = other->GetCollider().GetBounds().position;
    sf::Vector2f bSize = other->GetCollider().GetBounds().size;
    
    
    //   current right      otherposition.x   cur position.x    other right       current down       other up   current up    other down
    return aPos.x + aSize.x >= bPos.x && aPos.x <= bPos.x + bSize.x && aPos.y + aSize.y >= bPos.y && aPos.y <= bPos.y + bSize.y;
}
