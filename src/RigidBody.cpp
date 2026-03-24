#include "RigidBody.h"

RigidBody::RigidBody(sf::FloatRect bounds, ColliderType type, ColliderTag tag) 
    : _collider(bounds, type, tag)
{
}

void RigidBody::Update() {
    sf::Vector2f currentPosition = _collider.GetBounds().position;
    currentPosition += _velocity;
    SetPosition(currentPosition);
}
