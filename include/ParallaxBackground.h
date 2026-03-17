#pragma once
#include "Background.h"
#include "InputHandler.h"

class ParallexBackground {
private:
    Background _background;
    Background _clouds[3];
    Background _grounds[3];
    Background _trees[3];

public:
    ParallexBackground();
    void Start();
    void Update(const float& deltaTime, const InputAxis& inputAxis);
    void Render(sf::RenderWindow& window);
};