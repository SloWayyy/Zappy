/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#include "core.hpp"

Core::Core()
{
    this->_window = Window();
    this->_map = Map(10, 10);
    this->_menu = Menu();
}

void Core::initPlayer(void)
{
    character player(this->PING, 0, 0, {0, 1.0, 0});

    _characters.push_back(player);
}

void Core::run(void)
{
    this->_window.createWindow(1920, 1080, 60);
    this->initPlayer();
    this->_menu.init();
    this->_map.initMineral();
    while (!WindowShouldClose()) {
        switch (this->_window.getGameEvent()) {
            case MENU:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                this->_window.run();
                this->_menu.run();
                EndDrawing();
                break;
            case GAMEPLAY:
                // DisableCursor();
                BeginDrawing();
                ClearBackground(RAYWHITE);
                BeginMode3D(this->_window.getCamera());
                DrawFPS(10, 10);
                this->_window.run();
                this->_map.run();
                this->drawPlayers();
                EndMode3D();
                EndDrawing();
                break;
        }
    }
}

void Core::drawPlayers(void)
{
    for (auto &character : this->_characters)
        character.run();
}
