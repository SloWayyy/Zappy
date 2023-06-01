/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#include "src/Menu/Menu.hpp"

Menu::Menu(std::shared_ptr<Window> _window) : _window(_window)
{
    this->_background = this->_rayModel.loadTexture("assets/menu/background_menu.png");
    this->createButtons("PLAY", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 12.0f}, GOLD, 100, GAMEPLAY);
    this->createButtons("HOW TO PLAY", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 5.0f}, GOLD, 100, TUTO);
    this->createButtons("EXIT", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 3.0f}, GOLD, 100, EXIT);
    this->createButtons("SETTINGS", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 2.5f}, GOLD, 100, SETTINGS);
}

void Menu::draw()
{
    this->_rayModel.drawTexture(this->_background, 0, 0, RAYWHITE);
    this->drawButton();
}

void Menu::handleInput()
{
}

void Menu::run()
{
    this->draw();
    this->handleInput();
}

void Menu::createButtons(std::string string, coord_t coord, Color color, int size, GameEvent screen)
{
    this->_buttonsScreen.emplace_back(string, coord, color, size, screen, this->_window);
}

void Menu::drawButton(void)
{
    for (auto &button : this->_buttonsScreen) {
        button.update();
        this->_rayModel.drawRectangle(button.getCoord().x - 10, button.getCoord().y, button.getRectButton().width, button.getRectButton().height, button.getColorRect());
        this->_rayText.drawText(button.getString(), button.getCoord().x, button.getCoord().y, button.getSize(), button.getColor());
    }
}
