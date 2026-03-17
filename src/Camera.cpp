#include "Camera.h"

Camera::Camera(sf::RenderWindow& window, sf::Vector2f resolution) : _window(window) {
    _cameraResolution = resolution;
}

void Camera::Start() {
    _mainCamera = sf::View(sf::Vector2f(640, 360), _cameraResolution);
    _window.setView(_mainCamera);
}

void Camera::Update(const float& deltaTime) {
    _window.setView(_mainCamera);
}

void Camera::Move(sf::Vector2f moveDirection) {
    _mainCamera.move(moveDirection);
}
