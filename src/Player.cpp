#include "Player.h"

Player::Player(sf::RenderWindow& window) : _playerSprite(_playerIdleTexture),
_window(window)
{
    _playerIdleTexture.loadFromFile(_idleTexturePath);
    _playerWalkTexture.loadFromFile(_walkTexturePath);
    _playerAttackTexture.loadFromFile(_attackTexturePath);

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
    _playerSprite.setPosition({125, 625});
}

void Player::Update(const float& deltaTime, const InputHandler& inputHandler, Camera& camera) {
    _inputHandler = inputHandler;
    FlipSprite();

    if (_playerState != PlayerState::ATTACKING) {
        if (inputHandler.GetAxis().horizontal != 0) {
            _playerState = PlayerState::WALKING;
        }
        else _playerState = PlayerState::IDLE;
    }

    if (inputHandler.GetMouseEvent().mouseDown && _playerState != PlayerState::ATTACKING) {
        _playerState = PlayerState::ATTACKING;
    }

    PlayAnimation(deltaTime);
}

void Player::Render() {
    _window.draw(_playerSprite);
}

float currentAnimationTimer = 0.f;
int currentIdleKeyFrame = 0;
int currentWalkKeyFrame = 0;
int currentAttackKeyFrame = 0;

void Player::PlayAnimation(const float &deltaTime) {
    currentAnimationTimer += deltaTime;

    if (_playerState == PlayerState::IDLE) {

        if (&_playerSprite.getTexture() != &_playerIdleTexture) {
            _playerSprite.setTexture(_playerIdleTexture);
            currentWalkKeyFrame = 0;
            currentIdleKeyFrame = 0;  
            currentAnimationTimer = 0.f;  
            _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100}));
        }

        if (currentAnimationTimer > _animationDelay) {
            currentAnimationTimer = 0.f;
            currentIdleKeyFrame++;
            if (currentIdleKeyFrame >= _idleKeyFrames) currentIdleKeyFrame = 0;

            _playerSprite.setTextureRect(sf::IntRect({currentIdleKeyFrame * 100, 0}, {100,100}));
        }
    }

    else if (_playerState == PlayerState::WALKING) {
        if (&_playerSprite.getTexture() != &_playerWalkTexture) {
            _playerSprite.setTexture(_playerWalkTexture);
            currentIdleKeyFrame = 0;
            currentWalkKeyFrame = 0;  
            currentAnimationTimer = 0.f;
            _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100})); 
        }

        if (currentAnimationTimer > _animationDelay) {
            currentAnimationTimer = 0.f;
            currentWalkKeyFrame++;
            if (currentWalkKeyFrame >= _walkKeyFrames) currentWalkKeyFrame = 0;
            _playerSprite.setTextureRect(sf::IntRect({currentWalkKeyFrame * 100, 0}, {100, 100}));
        }
    }

    else if (_playerState == PlayerState::ATTACKING) {
        if (&_playerSprite.getTexture() != &_playerAttackTexture) {
            _playerSprite.setTexture(_playerAttackTexture);
            currentIdleKeyFrame = 0;
            currentWalkKeyFrame = 0; 
            currentAttackKeyFrame = 0; 
            currentAnimationTimer = 0.f;
            _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100})); 
        }

        if (currentAnimationTimer > _animationDelay) {
            currentAnimationTimer = 0.f;
            currentAttackKeyFrame++;
            if (currentAttackKeyFrame >= _attackKeyFrames) {
                currentAttackKeyFrame = 0;
                _playerState = PlayerState::IDLE;
            }
            _playerSprite.setTextureRect(sf::IntRect({currentAttackKeyFrame * 100, 0}, {100, 100}));
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

void Player::Movement(Camera &camera, float horizontal) {
}
