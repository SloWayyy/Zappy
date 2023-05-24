/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Main
*/

#include "../include/graphical.hpp"
#include "../include/character.hpp"
#include "raylib.h"

int main(void)
{
    graphical gui;
    character player;
    gui.init();
    player.init(10.0f, 1.0f, 5.0f);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(10, 10);
        BeginMode3D(gui.getCamera());
        gui.run();
        player.run();
        EndMode3D();
        EndDrawing();
    }
    player.stop();
    CloseWindow();
    return 0;
}
