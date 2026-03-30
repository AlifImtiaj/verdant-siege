#include "Player.h"

Player::Player(sf::RenderWindow& window, Camera& camera) : _playerSprite(_playerIdleTexture), _camera(camera),
_window(window)
{
    if (!_playerIdleTexture.loadFromFile(_idleTexturePath)) { printf("Idle texture couldn't be loaded\n"); }
    if (!_playerWalkTexture.loadFromFile(_walkTexturePath)) { printf("Walk texture couldn't be loaded\n"); }
    if (!_playerAttackTexture.loadFromFile(_attackTexturePath)) { printf("Idle texture couldn't be loaded\n"); }

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
    _playerSprite.setPosition({250, 550});

    
    _rb = RigidBody(sf::FloatRect({_playerSprite.getPosition().x , _playerSprite.getPosition().y}, {100,100}), ColliderType::DYNAMIC, ColliderTag::PLAYER);
}

void Player::Update(const float& deltaTime, InputHandler& inputHandler) {
    _inputHandler = inputHandler;
    if (_playerState != PlayerState::ATTACKING)
        FlipSprite();

    bPlayerMoving = false;
    bShouldBackgroundMove = false;
    _currentAnimationTimer += deltaTime;


    ChangeState(_inputHandler);
    Movement(deltaTime, inputHandler);
    UpdateAnimation();
    SetPosition();
}

void Player::Render() {
    _window.draw(_playerSprite);
    #ifdef _DEBUG
        _rb.GetCollider().DebugDraw(_window);
    #endif
}

void Player::PlayAnimation(sf::Texture& texture, int keyFrame) {
    // changes the texture, this code only run once every state changes
    if (&_playerSprite.getTexture() != &texture) {
        _playerSprite.setTexture(texture);
        _currentKeyFrame = 0;
        _playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 100}));
    }

    if (_currentAnimationTimer > _animationDelay) {
        _playerSprite.setTextureRect(sf::IntRect({_currentKeyFrame * 100, 0}, {100,100}));
        _currentAnimationTimer = 0.f;
        _currentKeyFrame++;
        if (_currentKeyFrame >= keyFrame) {
            _currentKeyFrame = 0;
            if (_playerState == PlayerState::ATTACKING)
                _playerState = PlayerState::IDLE;
        }
    }
}

void Player::SetPosition() {
    _position = _rb.GetCollider().GetBounds().position;
    // to offset position to the center of the collider
    _position.x += 50.f;
    _position.y += 50.f;
    // update sprite position
    _playerSprite.setPosition(_position);
}

void Player::UpdateAnimation()
{
    if (_playerState == PlayerState::IDLE)
        PlayAnimation(_playerIdleTexture, _idleKeyFrames);
    else if (_playerState == PlayerState::WALKING)
        PlayAnimation(_playerWalkTexture, _walkKeyFrames);
    else if (_playerState == PlayerState::ATTACKING) 
        PlayAnimation(_playerAttackTexture, _attackKeyFrames);
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

void Player::Movement(const float& deltaTime, InputHandler& inputHandler) {

    // add to devlog
    // to make the physics work. i need to get the velocity from rb
    // then just update the x
    sf::Vector2f moveDirection = _rb.GetVelocity();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _rb.IsGrounded())
        moveDirection.y = -250;
    
    
    if (_playerState == PlayerState::IDLE || _playerState == PlayerState::ATTACKING) {
        moveDirection.x = 0;
        _rb.SetVelocity(moveDirection);
        return;
    }

    float horizontal = inputHandler.GetAxis().horizontal;
    float vertical = inputHandler.GetAxis().vertical;
    moveDirection.x = _walkSpeed*horizontal;
    _rb.SetVelocity(moveDirection);

    bPlayerMoving = true;

    sf::Vector2f cameraPosition = _camera.GetCamera().getCenter();
    
    if (horizontal == 1.f && (_position.x - cameraPosition.x) > 400.f) {
        _camera.Move(moveDirection*deltaTime);
        bShouldBackgroundMove = true;
    }
    if (horizontal == -1.f & ((cameraPosition.x - _position.x) > 400.f)) {
        _camera.Move(moveDirection*deltaTime);
        bShouldBackgroundMove = true;
    }
}

void Player::ChangeState(InputHandler &inputHandler) {
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
}


