#include "World.h"


World::World(InputHandler& inputHandler, sf::RenderWindow& window) : 
    _inputHandler(inputHandler),
    _window(window),
    _camera(window, {1280.f, 720.f}),
    _player(window, _camera, {250, 300})
{
}

void World::Start() {
    _background.Start();
    _player.Start();
    _camera.Start();

    
    _physics.AddRigidBody(_player.GetRigidBody());
    _physics.AddRigidBody(_background.GetRigidBody());
}

void World::Update(const float& deltaTime) {

    
    _player.Update(deltaTime, _inputHandler);
    _camera.Update(deltaTime);
    
    InputAxis backgroundAxis = _player.ShouldBackgroundMove() ? _inputHandler.GetAxis() : InputAxis {};
    _background.Update(deltaTime, backgroundAxis, _camera, _player);
    
    _physics.Update(deltaTime);
}

void World::Render() {
    _background.Render(_window);
    _player.Render();
}

World::~World() {
    _physics.ClearRigidBody();
}
