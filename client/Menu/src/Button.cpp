/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** button
*/

#include "Menu/include/Button.hpp"

Button::Button(std::string string, coord_t coord, Color color, int size, GameEvent screen, const std::shared_ptr<Window> &ptr): _window(ptr)
{
    this->_string = string;
    this->_coord = coord;
    this->_colorFont = color;
    this->_size = size;
    this->_screen = screen;
    this->_colorRect = BLUE;
    this->_isClicked = false;
    this->_rectButton.x = this->getCoord().x;
    this->_rectButton.y = this->getCoord().y;
    this->_rectButton.width = this->getString().size() * this->getSize();
    this->_rectButton.height = 100;
    this->check = false;
    this->_click = false;
}

void Button::update()
{
    this->_colorFont = this->_colorFont;
    this->_colorRect = BLUE;
    this->_mouse.x = GetMouseX();
    this->_mouse.y = GetMouseY();
    bool collision = CheckCollisionRecs(this->_mouse, this->_rectButton);

    if (collision) {
        if (IsMouseButtonDown(0) == true) {
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
    if (this->_click == true && IsMouseButtonReleased(0) == true) {
        this->_window->setGameEvent(this->getScreen());
        this->check = false;
        this->_click = false;
    }
}

void Button::setCoord(coord_t coord)
{
    this->_coord = coord;
}

coord_t Button::getCoord() const
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
