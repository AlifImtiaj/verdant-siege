#include "InputHandler.h"

void InputHandler::Update(sf::RenderWindow& window) {
    if (!window.hasFocus()) {
        _axis.horizontal = 0.f;
        _axis.vertical = 0.f;
        _mouseEvent.mouseUp = false;
        _mouseEvent.mouseDown = false;
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        _axis.vertical = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        _axis.vertical =  1.f;
    else _axis.vertical = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        _axis.horizontal =  1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        _axis.horizontal = -1.f;
    else _axis.horizontal = 0.f;

    _mousePos = sf::Mouse::getPosition(window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        _mouseEvent.mouseUp = false;
        _mouseEvent.mouseDown = true;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _mouseEvent.mouseDown) {
        _mouseEvent.mouseDown = false;
        _mouseEvent.mouseUp = true; 
    }
}


