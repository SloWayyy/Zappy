/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tuto.cpp
*/

#include "Tuto.hpp"

Tuto::Tuto(std::shared_ptr<Window> window)
{
    try {
        this->_window = window;
        std::size_t width = this->_window->getScreenWidth();
        std::size_t height = this->_window->getScreenHeight();
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu_tuto.png");
        createButtons("BACK", {width / 50.0f, height / 30.0f}, GOLD, 50, MENU);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Tuto constructor failed");
    }
}

Tuto::~Tuto()
{
    this->_rayModel.unloadTexture(this->_background);
}

void Tuto::handleInput()
{
}
