#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.h"
#include "Camera.h"

enum class PlayerState {
    IDLE,
    WALKING,
    ATTACKING
};

class Player {
private:

    sf::Sprite _playerSprite;

    float _playerScale = 4.0f;
    float _walkSpeed = 120.f;
    
    bool bPlayerMoving = false;

    PlayerState _playerState;
    InputHandler _inputHandler;

    // texture and animations
    sf::Texture _playerIdleTexture;  
    sf::Texture _playerWalkTexture;
    sf::Texture _playerAttackTexture;

    // texture paths
    const std::string _idleTexturePath = "Resources/player/Idle.png";
    const std::string _walkTexturePath = "Resources/player/Walk.png";
    const std::string _attackTexturePath = "Resources/player/Attack.png";

    // to change the sprites
    float _currentAnimationTimer = 0.f;
    int _currentIdleKeyFrame = 0;
    int _currentWalkKeyFrame = 0;
    int _currentAttackKeyFrame = 0;

    // how long to change a sprite
    float _animationDelay = 0.12f;
    // determines how many frames there are in the animation
    int _idleKeyFrames = 6;
    int _walkKeyFrames = 8;
    int _attackKeyFrames = 6;
    
    bool bOnAttackAnimation = false;
    bool bShouldBackgroundMove = false;

    sf::RenderWindow& _window;

public:
    Player(sf::RenderWindow& window);
    void Start();
    void Update(const float& deltaTime, InputHandler& inputHandler, Camera& camera);
    void Render();

    const bool& IsPlayerMoving() const { return bPlayerMoving; }
    const bool& ShouldBackgroundMove() const { return bShouldBackgroundMove; }
    const sf::Vector2f& GetPlayerPosition() const { return _playerSprite.getPosition(); }

private:
    void PlayAnimation(const float& deltaTime);
    void FlipSprite();
    void Movement(Camera &camera, const float& deltaTime, InputHandler& inputHandler);

};