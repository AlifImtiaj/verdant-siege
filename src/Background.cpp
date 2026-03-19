#include "Background.h"

Background::Background(const std::filesystem::path filePath) : _texture(filePath), _sprite(_texture) {
    sf::Vector2u texSize = _texture.getSize();
    _sprite.setScale({
        1280.f / texSize.x,
        720.f  / texSize.y
    });
    _texture.setSmooth(false);
    _sprite.setPosition({0,0});
}

void Background::SetSpeed(float moveSpeed) {
    _moveSpeed = moveSpeed;
}

void Background::Update(const float &deltaTime, const InputAxis& axis, const sf::Vector2f& playerPosition) {
    sf::Vector2f moveDirection = {_moveSpeed * deltaTime * axis.horizontal, 0.f};
    _sprite.move(moveDirection);
}

void Background::Render(sf::RenderWindow &window) {
    window.draw(_sprite);
}

void Background::SetPosition(sf::Vector2f position) {
    _sprite.setPosition(position);
}
