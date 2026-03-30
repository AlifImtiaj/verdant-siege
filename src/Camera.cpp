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

void Camera::SetPosition(sf::Vector2f position) {
    _mainCamera.setCenter(position);
}

void Camera::Move(sf::Vector2f moveDirection)
{
    // setting moveDirection causing camera to move up and down while the player is walking
    // to the edges of the screen and jumping at the same time
    moveDirection.y = 0;
    _mainCamera.move(moveDirection);
}

void Camera::SetSize(sf::Vector2f size) {
    _mainCamera.setSize(size);
}
