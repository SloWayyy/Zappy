/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#include "Menu.hpp"

Menu::Menu(std::shared_ptr<Window> window)
{
    try {
        this->_window = window;
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu.png");
        createButtons("PLAY", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 12.0f}, GOLD, 100, GAMEPLAY);
        createButtons("HOW TO PLAY", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 5.0f}, GOLD, 100, TUTO);
        createButtons("EXIT", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 3.0f}, GOLD, 100, EXIT);
        createButtons("SETTINGS", {(float)this->_window->getScreenWidth() / 15.0f, this->_window->getScreenHeight() / 2.5f}, GOLD, 100, SETTINGS);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Menu constructor failed");
    }
}

void Menu::handleInput()
{
}
