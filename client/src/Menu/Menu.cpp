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
        std::size_t width = this->_window->getScreenWidth();
        std::size_t height = this->_window->getScreenHeight();
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu.png");
        createButtons("PLAY", {width / 15.0f, height / 12.0f}, GOLD, 100, GAMEPLAY);
        createButtons("HOW TO PLAY", {width / 15.0f, height / 5.0f}, GOLD, 100, TUTO);
        createButtons("EXIT", {width / 15.0f, height / 3.0f}, GOLD, 100, EXIT);
        createButtons("SETTINGS", {width / 15.0f, height / 2.5f}, GOLD, 100, SETTINGS);
        createText("Try to connect to the server", {width / 2.0f, height / 15.0f}, RED, 50);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Menu constructor failed");
    }
}

Menu::~Menu()
{
    this->_rayModel.unloadTexture(this->_background);
}

void Menu::handleInput()
{
}
