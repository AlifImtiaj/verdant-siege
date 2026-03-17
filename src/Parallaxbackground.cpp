#include "ParallaxBackground.h"


ParallexBackground::ParallexBackground() :
    _background("Resources/nature_5/1.png"),
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

    // _background.SetSpeed(-120.f);
    

    for (int i = 0; i < 3; ++i) {
        _clouds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _trees[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));
        _grounds[i].SetPosition(sf::Vector2f(1280 * (i-1), 0.f));

        _clouds[i].SetSpeed(-25.f);
        _grounds[i].SetSpeed(-65.f);
        _trees[i].SetSpeed(-120.f);
    }
}

void ParallexBackground::Update(const float& deltaTime, const InputAxis& inputAxis) {
        
    _background.Update(deltaTime, inputAxis);

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
    _background.Render(window);
    
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
