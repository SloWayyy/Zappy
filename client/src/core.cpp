/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#include "core.hpp"

Core::Core()
{
    this->window = Window();
    this->map = Map(10, 10);
    this->menu = Menu();
}

void Core::initPlayer(void)
{
    character player(this->PING, 0, 0, {0, 1.0, 0});
    characters.push_back(player);
}

void Core::run(void)
{
    window.createWindow(1920, 1080, 60);
    initPlayer();
    menu.init();
    map.initMineral();
    while (!WindowShouldClose()) {
        switch (window.getGameEvent()) {
            case MENU:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                window.run();
                menu.run();
                EndDrawing();
                break;
            case GAMEPLAY:
                // DisableCursor();
                BeginDrawing();
                ClearBackground(RAYWHITE);
                BeginMode3D(window.getCamera());
                DrawFPS(10, 10);
                window.run();
                map.run();
                drawPlayers();
                EndMode3D();
                EndDrawing();
                break;
        }
    }
}

void Core::drawPlayers(void)
{
    for (auto &character : characters)
        character.run();
}
