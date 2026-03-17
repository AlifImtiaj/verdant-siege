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
    sf::Texture _playerIdleTexture;  
    sf::Texture _playerWalkTexture;
    sf::Texture _playerAttackTexture;

    sf::Sprite _playerSprite;

    float _animationDelay = 0.12f;
    int _idleKeyFrames = 6;
    int _walkKeyFrames = 8;
    int _attackKeyFrames = 6;

    PlayerState _playerState;
    InputHandler _inputHandler;

    const std::string _idleTexturePath = "Resources/player/Idle.png";
    const std::string _walkTexturePath = "Resources/player/Walk.png";
    const std::string _attackTexturePath = "Resources/player/Attack.png";

    float _playerScale = 4.0f;

    bool bOnAttackAnimation = false;

    sf::RenderWindow& _window;

public:
    Player(sf::RenderWindow& window);
    void Start();
    void Update(const float& deltaTime, const InputHandler& inputHandler, Camera& camera);
    void Render();


private:
    void PlayAnimation(const float& deltaTime);
    void FlipSprite();
    void Movement(Camera& camera, float horizontal);

};