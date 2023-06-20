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
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu.png");
        createButtons("BACK", {width / 50.0f, height / 30.0f}, GOLD, 50, MENU);
        createText("HOW TO PLAY", {width / 2.0f, height / 30.0f}, RED, 100);
        createText("This is a monitor of the game", {width / 50.0f, height / 10.0f}, RAYWHITE, 50);
        createText("You can see the informations of the game", {width / 50.0f, height / 8.0f}, RAYWHITE, 50);
        createText("You can switch the view of the game : ", {width / 50.0f, height / 6.0f}, RAYWHITE, 50);
        createText("- Press R to set the cam to 3rd person", {width / 40.0f, height / 5.0f}, RAYWHITE, 50);
        createText("- Press TAB to set the cam to 1st person on a player", {width / 40.0f, height / 4.0f}, RAYWHITE, 50);
        createText("On First person cam, you are able to : ", {width / 50.0f, height / 3.0f}, RAYWHITE, 50);
        createText("- Move with Z, Q, S, D", {width / 40.0f, height / 2.8f}, RAYWHITE, 50);
        createText("- Rotate with the mouse", {width / 40.0f, height / 2.6f}, RAYWHITE, 50);
        createText("- Zoom with the mouse wheel", {width / 40.0f, height / 2.4f}, RAYWHITE, 50);
        createText("- To see the inventory of a player and informations", {width / 40.0f, height /2.2f}, RAYWHITE, 50);
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
