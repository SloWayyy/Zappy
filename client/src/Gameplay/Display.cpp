/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Display
*/

#include "Display.hpp"

Display::Display(std::shared_ptr<Window> _window) : _window(_window)
{
}

void Display::drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color)
{
    this->_rayWindow.endMode3D();
    this->_rayText.drawText(text, posX, posY, fontSize, color);
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Display::run()
{
    this->drawTextOnScreen("DISPLAY MODE", 20, this->_window->getScreenHeight() / 2, 10, BLACK);
}
