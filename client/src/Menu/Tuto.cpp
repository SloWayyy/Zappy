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
        this->_background = LoadTexture("client/assets/menu/background_menu.png");
        createButtons("BACK", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 30.0f}, GOLD, 50, MENU);
        createText("HOW TO PLAY", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 30.0f}, RED, 100);
        createText("This is a monitor of the game", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 10.0f}, RAYWHITE, 50);
        createText("You can see the informations of the game", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 8.0f}, RAYWHITE, 50);
        createText("You can switch the view of the game : ", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 6.0f}, RAYWHITE, 50);
        createText("- Press R to set the cam to 3rd person", {(float)this->_window->getScreenWidth() / 40.0f, this->_window->getScreenHeight() / 5.0f}, RAYWHITE, 50);
        createText("- Press TAB to set the cam to 1st person on a player", {(float)this->_window->getScreenWidth() / 40.0f, this->_window->getScreenHeight() / 4.0f}, RAYWHITE, 50);
        createText("On First person cam, you are able to : ", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 3.0f}, RAYWHITE, 50);
        createText("- Move with Z, Q, S, D", {(float)this->_window->getScreenWidth() / 40.0f, this->_window->getScreenHeight() / 2.8f}, RAYWHITE, 50);
        createText("- Rotate with the mouse", {(float)this->_window->getScreenWidth() / 40.0f, this->_window->getScreenHeight() / 2.6f}, RAYWHITE, 50);
        createText("- Zoom with the mouse wheel", {(float)this->_window->getScreenWidth() / 40.0f, this->_window->getScreenHeight() / 2.4f}, RAYWHITE, 50);
        createText("- To see the inventory of a player and informations", {(float)this->_window->getScreenWidth() / 40.0f, this->_window->getScreenHeight() /2.2f}, RAYWHITE, 50);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Tuto constructor failed");
    }
}

void Tuto::handleInput()
{
}