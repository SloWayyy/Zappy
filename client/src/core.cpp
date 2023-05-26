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
}

void Core::initPlayer(void)
{
    character player;
    player.init(10.0f, 1.0f, 5.0f);
    characters.push_back(player);
}

void Core::run(void)
{
    window.createWindow(1920, 1080, 60);
    // initPlayer();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawFPS(10, 10);
        // BeginMode3D(window.getCamera());
        // window.run();
        // map.run();
        // for (auto &character : characters)
        //     character.run();
        EndMode3D();
        EndDrawing();
    }
}
