#include "ParallaxBackground.h"


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
    float playerSpeed = 120.f;
    
    for (int i = 0; i < 3; ++i) {

        // _backgrounds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _clouds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _trees[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _grounds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        
        _clouds[i].SetSpeed(playerSpeed * 0.8f);  // 36  - distant
        _grounds[i].SetSpeed(playerSpeed * 0.6f); // 72  - mid distance  
        _trees[i].SetSpeed(playerSpeed * 0.f);   // 96  - close, almost full speed
    }
}

void ParallexBackground::Update(const float& deltaTime, const InputAxis& inputAxis, Camera& camera) {
    
    // to position the background to be center always
    sf::Vector2f cameraCenter = camera.GetCamera().getCenter();

    _backgrounds[0].SetPosition({cameraCenter.x - 640.f, 0.f});
    // for (int i = 0; i < 3; ++i) {
    //     _backgrounds[i].SetPosition({cameraCenter.x - 1280.f + (1280.f * i), 0.f});
    // }

    for (auto& cloud: _clouds) {
        cloud.Update(deltaTime, inputAxis);
    }

    for (auto& ground: _grounds) {
        ground.Update(deltaTime, inputAxis);
    }

    for (auto& tree: _trees) {
        tree.Update(deltaTime, inputAxis);
    }
}

void ParallexBackground::Render(sf::RenderWindow& window) {
    // for (Background& background : _backgrounds) {
    //     background.Render(window);
    // }

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
}
