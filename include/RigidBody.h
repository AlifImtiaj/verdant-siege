#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class RigidBody {

private:
    sf::Vector2f _velocity = {0.f, 0.f};
    float _gravityScale = 1.f;
    bool bIsGrounded = false;
    Collider _collider;


public:
    RigidBody() = default;
    RigidBody(sf::FloatRect bounds, ColliderType type, ColliderTag tag);

    void SetPosition(sf::Vector2f position) { _collider.SetPosition(position); }
    void SetVelocity(sf::Vector2f velocity) { _velocity = velocity; }
    void SetGravityScale(float gravityScale) { _gravityScale = gravityScale; }
    void SetGrounded(bool isGrounded) { bIsGrounded = isGrounded; }

    sf::Vector2f GetVelocity() const { return _velocity; }
    float GetGravityScale() const { return _gravityScale; }
    bool IsGrounded() const { return bIsGrounded; }
    const Collider& GetCollider() const { return _collider; }
    Collider& GetCollider() { return _collider; }

    void Update();

};