/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gameover.cpp
*/

#include "Gameover.hpp"

Gameover::Gameover(std::shared_ptr<Window> window)
{
    try {
        this->_window = window;
        std::size_t width = this->_window->getScreenWidth();
        std::size_t height = this->_window->getScreenHeight();
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu.png");
        createButtons("EXIT", {width / 50.0f, height / 30.0f}, GOLD, 50, EXIT);
        createText("AND THE WINNER IS", {width / 3.0f, height / 10.0f}, RED, 100);
        createText("Team1", {width / 2.0f, height / 5.0f}, BLACK, 200);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Gameover constructor failed");
    }
}

Gameover::~Gameover()
{
    this->_rayModel.unloadTexture(this->_background);
}

void Gameover::handleInput()
{
    if (IsKeyPressed(KEY_ESCAPE))
        this->_window->setGameEvent(EXIT);
}
