#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "Inputhandler.h"

class Background {
public:

private:
    sf::Texture _texture;
    sf::Sprite _sprite;

    float _moveSpeed = 0.f;

public:
    Background(const std::filesystem::path filePath);
    void SetSpeed(float moveSpeed);
    void Update(const float& deltaTime, const InputAxis& axis);
    void Render(sf::RenderWindow& window);

    void SetPosition(sf::Vector2f position);

private:


};