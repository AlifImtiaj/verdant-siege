#include "World.h"


World::World(InputHandler& inputHandler, sf::RenderWindow& window) : _inputHandler(inputHandler),
 _window(window),
  _camera(window, {1280.f, 720.f}),
  _player(window, _camera) {
}

void World::Start() {
    _background.Start();
    _player.Start();
    _camera.Start();

    
    _physics.AddRigidBody(_player.GetRigidBody());
    _physics.SetCollider(_background.GetRigidBody()->GetCollider());
}

void World::Update(const float& deltaTime) {

    _physics.Update(deltaTime);

    _player.Update(deltaTime, _inputHandler);

    InputAxis backgroundAxis = _player.ShouldBackgroundMove() ? _inputHandler.GetAxis() : InputAxis {};

    _background.Update(deltaTime, backgroundAxis, _camera, _player);
    _camera.Update(deltaTime);
}

void World::Render() {
    _background.Render(_window);
    _player.Render();
}

World::~World() {
    
}
