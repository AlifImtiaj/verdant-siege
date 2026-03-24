#include "Collider.h"

Collider::Collider(sf::FloatRect bounds, ColliderType type, ColliderTag tag) 
    : _bounds(bounds), _type(type), _tag(tag) {}

void Collider::DebugDraw(sf::RenderWindow &window) {
    sf::RectangleShape rect(_bounds.size);
    rect.setPosition(_bounds.position);
    rect.setFillColor(sf::Color::Transparent);

    switch (_type) {
        case ColliderType::STATIC:    rect.setOutlineColor(sf::Color::Green);  break;
        case ColliderType::KINEMATIC: rect.setOutlineColor(sf::Color::Blue);   break;
        case ColliderType::DYNAMIC:   rect.setOutlineColor(sf::Color::Red);    break;
    }

    rect.setOutlineThickness(1.f);

    window.draw(rect);
}
