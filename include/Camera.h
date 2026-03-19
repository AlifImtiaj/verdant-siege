#pragma once

#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::View _mainCamera;
    sf::RenderWindow& _window;
    sf::Vector2f _cameraResolution;

public:
    Camera() = default;
    Camera(sf::RenderWindow& window, sf::Vector2f resolution);
    void Start();
    void Update(const float& deltaTime);
    
    void SetPosition (sf::Vector2f position);
    void Move(sf::Vector2f moveDirection);
    const sf::View& GetCamera() const { return _mainCamera; }
    
    void SetSize(sf::Vector2f size);

};