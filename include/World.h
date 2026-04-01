#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.h"
#include "ParallaxBackground.h"
#include "Player.h"
#include "PhysicsWorld.h"
#include "Camera.h"

class World {
private:
    InputHandler& _inputHandler;
    sf::RenderWindow& _window;
    Camera _camera;

    ParallexBackground _background;
    Player _player;

    PhysicsWorld _physics;
    float deltaTime;

public:
    World(InputHandler& inputHandler, sf::RenderWindow& window); // use constructor only to assign values, dont do any instructions here, causes bug sometime
    void Start(); // call this instead of default constructor, for using instructions
    void Update(const float& deltaTime);
    void Render();
    ~World();

private:

};