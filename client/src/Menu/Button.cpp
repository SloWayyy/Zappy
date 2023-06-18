/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** button
*/

#include "src/Menu/Button.hpp"

Button::Button(std::string string, coord coord, Color color, int size, GameEvent screen, const std::shared_ptr<Window> &ptr): _window(ptr), _string(string), _coord(coord), _colorFont(color), _size(size), _screen(screen), _colorRect(BLUE), _isClicked(false), _click(false), check(false)
{
    this->_rectButton.x = this->getCoord().x;
    this->_rectButton.y = this->getCoord().y;
    this->_rectButton.width = this->getString().size() * this->getSize();
    this->_rectButton.height = 100;
}

void Button::update()
{
    this->_colorRect = BLUE;
    this->_mouse.x = this->_rayMouse.getMouseX();
    this->_mouse.y = this->_rayMouse.getMouseY();
    this->_mouse.width = 1;
    this->_mouse.height = 1;
    bool collision = this->_rayMouse.checkCollisionRecs(this->_mouse, this->_rectButton);

    if (collision) {
        if (this->_rayMouse.isMouseButtonDown(0) == true) {
            this->_colorFont = GOLD;
            this->_colorRect = PURPLE;
            this->_click = true;
        } else {
            this->check = true;
            this->_colorFont = BLUE;
            this->_colorRect = GOLD;
        }
    }
    if (this->check == true && collision == false) {
        this->_colorFont = GOLD;
        this->_colorRect = BLUE;
    }
    if (this->_click == true && this->_rayMouse.isMouseButtonReleased(0) == true) {
        this->check = false;
        this->_click = false;
        this->_colorFont = GOLD;
        this->_colorRect = BLUE;
        this->_window->setGameEvent(this->getScreen());
    }
}

void Button::setCoord(coord coord)
{
    this->_coord = coord;
}

coord Button::getCoord() const
{
    return this->_coord;
}

void Button::setString(std::string string)
{
    this->_string = string;
}

std::string Button::getString() const
{
    return this->_string;
}

void Button::setColor(Color color)
{
    this->_colorFont = color;
}

Color Button::getColor() const
{
    return this->_colorFont;
}

void Button::setSize(int size)
{
    this->_size = size;
}

int Button::getSize() const
{
    return this->_size;
}

void Button::setScreen(GameEvent screen)
{
    this->_screen = screen;
}

GameEvent Button::getScreen() const
{
    return this->_screen;
}

Rectangle Button::getRectButton() const
{
    return this->_rectButton;
}

Color Button::getColorRect() const
{
    return this->_colorRect;
}

bool Button::getIsClicked() const
{
    return this->_isClicked;
}

void Button::setIsClicked(bool isClicked)
{
    this->_isClicked = isClicked;
}

bool Button::MouseClickedOnButton(int x, int y)
{
    if (x >= this->_coord.x && x <= this->_coord.x + this->_rectButton.width && y >= this->_coord.y && y <= this->_coord.y + this->_rectButton.height)
        return true;
    return false;
}