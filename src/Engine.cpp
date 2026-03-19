#include "Engine.h"

#include <imgui.h>
#include <imgui-SFML.h>

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
    if (!ImGui::SFML::Init(_window)) {
        printf("ImGui Init failed\n");
        bGameRunning = false;
        return;
    }
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
        ImGui::SFML::ProcessEvent(_window, *event);
        if (event->getIf<sf::Event::Closed>()) {
            bGameRunning = false;
        }
    }
}

// bool bFullScreen = false;
// bool bWindowLastState = true;

void Engine::Update() {
    sf::Time deltaTime = _gameClock.restart();
    float dt = deltaTime.asSeconds();
    _inputHandler.Update(_window);
    ImGui::SFML::Update(_window, deltaTime);

    // bWindowLastState = bFullScreen;
    // ImGui::Begin("Window");
    // ImGui::Checkbox("Fullscreen", &bFullScreen);
    // ImGui::End();
    // if (bWindowLastState != bFullScreen) {
    //     bFullScreen ? _window.create(sf::VideoMode({_windowWidth, _windowHeight}),"Game Window", sf::State::Fullscreen) :
    //     _window.create(sf::VideoMode({_windowWidth, _windowHeight}),"Game Window", sf::State::Windowed);
    // }
    

    _world.Update(dt);
}

void Engine::Render() {
    
    _window.clear();
    
    _world.Render();

    // imgui should always render at last
    ImGui::SFML::Render(_window);
    _window.display();
}

Engine::~Engine() {
    ImGui::SFML::Shutdown();
    _window.close();
}