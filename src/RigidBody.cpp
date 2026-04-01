#include "RigidBody.h"

RigidBody::RigidBody(sf::FloatRect bounds, ColliderType type, ColliderTag tag) 
    : _collider(bounds, type, tag)
{
}

void RigidBody::Update(const float& deltaTime) {
    sf::Vector2f currentPosition = _collider.GetBounds().position;
    currentPosition += _velocity * deltaTime;
    SetPosition(currentPosition);
}
