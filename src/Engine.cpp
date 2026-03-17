#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height, const std::string &title) :
_window(sf::VideoMode({width, height}), title),
 _world(_inputHandler, _window) {


    _windowHeight = height;
    _windowWidth = width;
    bGameRunning = true;
    _window.setFramerateLimit(60u);

    sf::Image icon = sf::Image("Resources/icon.png");
    _window.setIcon(icon);
}

void Engine::Run() {
    Start();

    while(bGameRunning) {
        HandleInput();
        Update();
        Render();
    }

}

void Engine::Start() {
    _world.Start();
}

void Engine::HandleInput() {
    while (std::optional<sf::Event> event = _window.pollEvent()) {
        if (event->getIf<sf::Event::Closed>()) {
            bGameRunning = false;
        }
    }
}

void Engine::Update() {
    float dt = _gameClock.restart().asSeconds();
    _inputHandler.Update(_window);

    _world.Update(dt);
}

void Engine::Render() {
    
    _window.clear();
    // render everything here
    _world.Render();

    _window.display();
}

Engine::~Engine() {
    _window.close();
}