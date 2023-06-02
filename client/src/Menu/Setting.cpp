/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setting.cpp
*/

#include "Setting.hpp"

Setting::Setting(std::shared_ptr<Window> window)
{
    this->_window = window;
    this->_background = LoadTexture("assets/menu/background_menu.png");
    createButtons("BACK", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 30.0f}, GOLD, 50, MENU);
    createText("SETTINGS", {(float)this->_window->getScreenWidth() / 1.5f, this->_window->getScreenHeight() / 30.0f}, RED, 100);
    createText("Volumes :", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 10.0f}, RAYWHITE, 50);
    createButtons("+", {(float)this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
    createButtons("-", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
    createText("FPS :", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 5.0f}, RAYWHITE, 50);
    createButtons("<", {(float)this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 4.0f}, PINK, 50, SETTINGS);
    createButtons(">", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 4.0f}, PINK, 50, SETTINGS);
    createText("Météo :", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 3.0f}, RAYWHITE, 50);
}

void Setting::handleInput()
{
}