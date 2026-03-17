#include "World.h"


World::World(InputHandler& inputHandler, sf::RenderWindow& window) : _inputHandler(inputHandler),
 _window(window),
  _camera(window, (sf::Vector2f)window.getSize()),
  _player(window) {
}

void World::Start() {
    _background.Start();
    _player.Start();
    _camera.Start();
}

void World::Update(const float& deltaTime) {

    _inputHandler.Update(_window);
    _camera.Update(deltaTime);
    _background.Update(deltaTime, _inputHandler.GetAxis());
    _player.Update(deltaTime, _inputHandler, _camera);
    
    
}

void World::Render() {
    _background.Render(_window);
    _player.Render();
}

World::~World() {
    
}
