#include "ParallaxBackground.h"
#include "imgui.h"

ParallexBackground::ParallexBackground() :
    _backgrounds{
        Background("Resources/nature_5/1.png"),
        Background("Resources/nature_5/1.png"),
        Background("Resources/nature_5/1.png")
    },
    _clouds{
        Background("Resources/nature_5/2.png"),
        Background("Resources/nature_5/2.png"),
        Background("Resources/nature_5/2.png")
    },
    _grounds{
        Background("Resources/nature_5/3.png"),
        Background("Resources/nature_5/3.png"),
        Background("Resources/nature_5/3.png")
    },
    _trees{
        Background("Resources/nature_5/4.png"),
        Background("Resources/nature_5/4.png"),
        Background("Resources/nature_5/4.png")
    }
{
}

void ParallexBackground::Start()
{
    _rb = RigidBody(sf::FloatRect({0,675}, {2000,50}), ColliderType::STATIC, ColliderTag::PLATFORM);
    for (int i = 0; i < 3; ++i) {
        // evenly places the background sprites
        _clouds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _trees[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _grounds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));

    }
}


float previousSpeed;
float currentSpeed = 0.f;
void ParallexBackground::Update(const float& deltaTime, const InputAxis& inputAxis, Camera& camera, const Player& player) {
    
    // to position the background to be center always
    sf::Vector2f cameraCenter = camera.GetCamera().getCenter();
    _backgrounds[0].SetPosition({cameraCenter.x - 640.f, 0.f});

    float scrollSpeed = player.GetWalkSpeed();
    previousSpeed = scrollSpeed;
    // run this part of code only when speed is changed, not every update loop
    if (previousSpeed != currentSpeed) {
        for (int i = 0; i < 3; ++i) {
            _clouds[i].SetSpeed(scrollSpeed * 0.8f);  // 80% of player speed, making it feel like farthest
            _grounds[i].SetSpeed(scrollSpeed * 0.6f); // 60% of player speed, make it far, but not far away as like the clouds
            _trees[i].SetSpeed(scrollSpeed * 0.f);   // static
        }
                
    }
    currentSpeed = previousSpeed;

    sf::Vector2f position = player.GetPosition();
    for (auto& cloud: _clouds) {
        cloud.Update(deltaTime, inputAxis, position);
    }

    for (auto& ground: _grounds) {
        ground.Update(deltaTime, inputAxis, position);
    }

    for (auto& tree: _trees) {
        tree.Update(deltaTime, inputAxis, position);
    }
}

void ParallexBackground::Render(sf::RenderWindow& window) {

    _backgrounds[0].Render(window);
    
    for (Background& cloud : _clouds) {
        cloud.Render(window);
    }

    for (Background& ground : _grounds) {
        ground.Render(window);
    }
    for (auto& tree: _trees) {
        tree.Render(window);
    }
    #ifdef _DEBUG
        _rb.GetCollider().DebugDraw(window);
    #endif
}
