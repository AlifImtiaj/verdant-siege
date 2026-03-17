#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.h"
#include "ParallaxBackground.h"
#include "Player.h"
#include "Camera.h"

class World {
private:
    InputHandler& _inputHandler;
    Camera _camera;
    sf::RenderWindow& _window;

    ParallexBackground _background;
    Player _player;

public:
    World(InputHandler& inputHandler, sf::RenderWindow& window); // use constructor only to assign values, dont do any instructions here, causes bug sometime
    void Start(); // call this instead of default constructor, for using instructions
    void Update(const float& deltaTime);
    void Render();
    ~World();

private:

};