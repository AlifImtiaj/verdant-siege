#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"
#include "InputHandler.h"

#ifdef _DEBUG
    inline bool DEBUG_DRAW = false;
#endif

class Engine {
private:
    sf::RenderWindow _window;
    unsigned int _windowHeight;
    unsigned int _windowWidth;

    bool bGameRunning = true;

    InputHandler _inputHandler;
    World _world;

    sf::Clock _gameClock;

public:
    Engine(unsigned int width, unsigned int height, const std::string& title);
    void Run();
    ~Engine();

private:
    void Start();
    void HandleInput();
    void Update();
    void Render();

};