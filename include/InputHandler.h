#pragma once
#include <SFML/Graphics.hpp>

struct InputAxis {
    float horizontal = 0.f;
    float vertical = 0.f;
};

struct MouseEvent {
    bool mouseDown = false;
    bool mouseUp = false;
};

class InputHandler {
public:
    void Update(sf::RenderWindow& window);
    const InputAxis& GetAxis() const { return _axis; }
    const sf::Vector2i& GetMousePos() const { return _mousePos; }
    const MouseEvent& GetMouseEvent() const { return _mouseEvent; }

private:
    InputAxis _axis;
    sf::Vector2i _mousePos;
    MouseEvent _mouseEvent;

};