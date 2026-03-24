#pragma once
#include <SFML/Graphics.hpp>

enum class ColliderType {
    DYNAMIC,
    STATIC,
    KINEMATIC
};

enum class ColliderTag {
    PLAYER,
    PLATFORM,
    ENEMY,
    PLAYER_SWORD,
    ENEMY_SWORD
};

class Collider {
private:
    sf::FloatRect _bounds;
    ColliderType _type = ColliderType::STATIC;
    ColliderTag _tag = ColliderTag::PLATFORM;

public:
    Collider() = default;
    Collider(sf::FloatRect bounds, ColliderType type, ColliderTag tag);

    void DebugDraw(sf::RenderWindow& window);

    void SetPosition(sf::Vector2f position) { _bounds.position = position; }
    void SetBounds(sf::FloatRect bounds) { _bounds = bounds; }

    const sf::FloatRect& GetBounds() const { return _bounds; }

    ColliderType GetType() const { return _type; }
    ColliderTag GetTag() const { return _tag; } 


};