#pragma once
#include <vector>

#include "Background.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Player.h"
#include "RigidBody.h"

class ParallexBackground {
private:
    Background _backgrounds[3];
    Background _clouds[3];
    Background _grounds[3];
    Background _trees[3];
    std::vector<RigidBody> _rb;
public:
    ParallexBackground();
    void Start();
    void Update(const float& deltaTime,
            const InputAxis& inputAxis,
            Camera& camera,
            const Player& player
        );
    void Render(sf::RenderWindow& window);


    std::vector<RigidBody>& GetRigidBody() { return _rb; }
};