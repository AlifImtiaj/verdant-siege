#pragma once
#include "Background.h"
#include "InputHandler.h"
#include "Camera.h"

class ParallexBackground {
private:
    Background _backgrounds[3];
    Background _clouds[3];
    Background _grounds[3];
    Background _trees[3];

public:
    ParallexBackground();
    void Start();
    void Update(const float& deltaTime, const InputAxis& inputAxis, Camera& camera);
    void Render(sf::RenderWindow& window);
};