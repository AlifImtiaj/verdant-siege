#include "Player.h"

#include <imgui.h>
#include <imgui-SFML.h>

Player::Player(sf::RenderWindow& window) : _playerSprite(_playerIdleTexture),
_window(window)
{
    if (!_playerIdleTexture.loadFromFile(_idleTexturePath)) { printf("Idle texture couldn't be loaded"); }
    if (!_playerWalkTexture.loadFromFile(_walkTexturePath)) { printf("Walk texture couldn't be loaded"); }
    if (!_playerAttackTexture.loadFromFile(_attackTexturePath)) { printf("Idle texture couldn't be loaded"); }

    _playerIdleTexture.setSmooth(false);
    _playerWalkTexture.setSmooth(false);
    _playerAttackTexture.setSmooth(false);

    _playerSprite.setTexture(_playerIdleTexture);
    _playerSprite.setOrigin({50.f, 50.f});

    _playerSprite.setTextureRect(sf::IntRect({0,0},{100,100}));
    _playerSprite.setScale({_playerScale, _playerScale});
}

void Player::Start() {
    _playerState = PlayerState::IDLE;
    _playerSprite.setPosition({300, 625});
}

void Player::Update(const float& deltaTime, InputHandler& inputHandler, Camera& camera) {
    _inputHandler = inputHandler;
    FlipSprite();

    bPlayerMoving = false;
    bShouldBackgroundMove = false;

    if (_playerState != PlayerState::ATTACKING) {
        if (inputHandler.GetAxis().horizontal != 0) {
            _playerState = PlayerState::WALKING;
        }
        else {
            _playerState = PlayerState::IDLE;
        }
    }

    if (inputHandler.GetMouseEvent().mouseDown && _playerState != PlayerState::ATTACKING) {
        _playerState = PlayerState::ATTACKING;
    }
    Movement(camera, deltaTime, inputHandler);
    PlayAnimation(deltaTime);
}

void Player::Render() {
    _window.draw(_playerSprite);
}



void Player::PlayAnimation(const float &deltaTime) {
    _currentAnimationTimer += deltaTime;

    if (_playerState == PlayerState::IDLE) {

        // changes the texture, this code only run once every state changes
        if (&_playerSprite.getTexture() != &_playerIdleTexture) {
            _playerSprite.setTexture(_playerIdleTexture);
            _currentWalkKeyFrame = 0;
            _currentIdleKeyFrame = 0;  
            _currentAnimationTimer = 0.f;  
            _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100}));
        }

        if (_currentAnimationTimer > _animationDelay) {
            _playerSprite.setTextureRect(sf::IntRect({_currentIdleKeyFrame * 100, 0}, {100,100}));
            _currentAnimationTimer = 0.f;
            _currentIdleKeyFrame++;
            if (_currentIdleKeyFrame >= _idleKeyFrames) _currentIdleKeyFrame = 0;

        }
    }

    else if (_playerState == PlayerState::WALKING) {
        // changes the texture, this code only run once every state changes
        if (&_playerSprite.getTexture() != &_playerWalkTexture) {
            _playerSprite.setTexture(_playerWalkTexture);
            _currentIdleKeyFrame = 0;
            _currentWalkKeyFrame = 0;  
            _currentAnimationTimer = 0.f;
            _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100})); 
        }

        if (_currentAnimationTimer > _animationDelay) {
            _playerSprite.setTextureRect(sf::IntRect({_currentWalkKeyFrame * 100, 0}, {100, 100}));
            _currentAnimationTimer = 0.f;
            _currentWalkKeyFrame++;
            if (_currentWalkKeyFrame >= _walkKeyFrames) _currentWalkKeyFrame = 0;
        }
    }

    else if (_playerState == PlayerState::ATTACKING) {
        // changes the texture, this code only run once every state changes
        if (&_playerSprite.getTexture() != &_playerAttackTexture) {
            _playerSprite.setTexture(_playerAttackTexture);
            _currentIdleKeyFrame = 0;
            _currentWalkKeyFrame = 0; 
            _currentAttackKeyFrame = 0; 
            _currentAnimationTimer = 0.f;
            _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100})); 
        }

        if (_currentAnimationTimer > _animationDelay) {
            _playerSprite.setTextureRect(sf::IntRect({_currentAttackKeyFrame * 100, 0}, {100, 100}));
            _currentAnimationTimer = 0.f;
            _currentAttackKeyFrame++;

            if (_currentAttackKeyFrame >= _attackKeyFrames) {
                _currentAttackKeyFrame = 0;
                _playerState = PlayerState::IDLE;
            }
        }
    }
}

void Player::FlipSprite() {
    if (_inputHandler.GetAxis().horizontal == -1) {
        if (_playerSprite.getScale() != sf::Vector2f(-_playerScale, _playerScale))
            _playerSprite.setScale({-_playerScale,_playerScale});
    }

    if (_inputHandler.GetAxis().horizontal == 1) {
        if (_playerSprite.getScale() != sf::Vector2f(_playerScale, _playerScale))
            _playerSprite.setScale({_playerScale,_playerScale});
    }
}

void Player::Movement(Camera &camera, const float& deltaTime, InputHandler& inputHandler) {
    if (_playerState == PlayerState::IDLE || _playerState == PlayerState::ATTACKING) return;

    bPlayerMoving = true;

    float horizontal = inputHandler.GetAxis().horizontal;
    float vertical = inputHandler.GetAxis().vertical;
    
    sf::Vector2f moveDirection = sf::Vector2f(_walkSpeed*deltaTime*horizontal, 0);

    sf::Vector2f playerPosition = _playerSprite.getPosition();
    sf::Vector2f cameraPosition = camera.GetCamera().getCenter();



    _playerSprite.move(moveDirection);
    if (horizontal == 1.f && (playerPosition.x - cameraPosition.x) > 400.f) {
        camera.Move(moveDirection);
        bShouldBackgroundMove = true;
    }
    if (horizontal == -1.f & ((cameraPosition.x - playerPosition.x) > 400.f)) {
        camera.Move(moveDirection);
        bShouldBackgroundMove = true;
    }
}
