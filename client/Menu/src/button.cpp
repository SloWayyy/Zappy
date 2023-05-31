/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** button
*/

#include "Menu/include/button.hpp"

buttons::buttons(std::string string, coord_t coord, Color color, int size, GameEvent screen, const std::shared_ptr<Window> &ptr): _window(ptr)
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

void buttons::update()
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
