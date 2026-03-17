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

void Background::Update(const float &deltaTime, const InputAxis& axis) {
    
    sf::Vector2f moveDirection = {_moveSpeed * deltaTime * axis.horizontal, 0.f};
    _sprite.move(moveDirection);

    // if (_sprite.getPosition().x < -1920) {
    //     _sprite.setPosition({1920, 0});
    // }
    // else if (_sprite.getPosition().x > 1920) {
    //     _sprite.setPosition({-1920, 0});
    // }

}

void Background::Render(sf::RenderWindow &window) {
    window.draw(_sprite);
}

void Background::SetPosition(sf::Vector2f position) {
    _sprite.setPosition(position);
}
