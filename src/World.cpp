#include "World.h"


World::World(InputHandler& inputHandler, sf::RenderWindow& window) : _inputHandler(inputHandler),
 _window(window),
  _camera(window, {1280.f, 720.f}),
  _player(window) {
}

void World::Start() {
    _background.Start();
    _player.Start();
    _camera.Start();
}

void World::Update(const float& deltaTime) {
    _player.Update(deltaTime, _inputHandler, _camera);

    InputAxis backgroundAxis = _player.ShouldBackgroundMove() ? _inputHandler.GetAxis() : InputAxis {};

    _background.Update(deltaTime, backgroundAxis, _camera);
    _camera.Update(deltaTime);
}

void World::Render() {
    _background.Render(_window);
    _player.Render();
}

World::~World() {
    
}
