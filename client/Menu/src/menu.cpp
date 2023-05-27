/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#include "Menu/include/menu.hpp"

Menu::Menu()
{
}

void Menu::init()
{
    this->_background = LoadTexture("assets/menu/background_menu.png");
}

void Menu::draw()
{
    drawTexture(this->_background, 0, 0, RAYWHITE);
}

void Menu::handleInput()
{
}

void Menu::stop()
{
    UnloadTexture(this->_background);
}

void Menu::run()
{
    this->draw();
    this->handleInput();
}