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
        this->_background = LoadTexture("client/assets/menu/background_menu.png");
        createButtons("EXIT", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 30.0f}, GOLD, 50, EXIT);
        createText("AND THE WINNER IS", {(float)this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 10.0f}, RED, 100);
        createText("Team1", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 5.0f}, BLACK, 200);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Gameover constructor failed");
    }
}

void Gameover::handleInput()
{
    if (IsKeyPressed(KEY_ESCAPE))
        this->_window->setGameEvent(EXIT);
}
