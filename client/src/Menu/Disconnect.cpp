/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Disconnect.cpp
*/

#include "Disconnect.hpp"

Disconnect::Disconnect(std::shared_ptr<Window> window)
{
    this->_window = window;
    std::size_t width = this->_window->getScreenWidth();
    std::size_t height = this->_window->getScreenHeight();

    createButtons("EXIT", {width / 50.0f, height / 30.0f}, GOLD, 50, EXIT);
    createText("You have been disconnected", {width / 3.5f, height / 10.0f}, RED, 100);
    createText("Because the server is down", {width / 2.0f, height / 5.0f}, BLACK, 50);
    createButtons("MENU", {width / 1.2f - 50, height / 3.0f}, GOLD, 50, MENU);
}

Disconnect::~Disconnect()
{
}

void Disconnect::handleInput()
{
    if (IsKeyPressed(KEY_ESCAPE))
        this->_window->setGameEvent(EXIT);
}