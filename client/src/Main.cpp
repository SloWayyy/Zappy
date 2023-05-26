/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Main
*/

#include "raylib.h"
#include "character.hpp"
#include "encapsulation/Raylibcpp.hpp"
#include "core.hpp"
#include <memory>

int main(void)
{
    // graphical gui;
    // character player;
    // gui.init();
    // player.init(10.0f, 1.0f, 5.0f);
    // gui.players.push_back(player);
    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);
    //     DrawFPS(10, 10);
    //     BeginMode3D(gui.getCamera());
    //     gui.run();
    //     EndMode3D();
    //     EndDrawing();
    // }
    // player.stop();
    // CloseWindow();
    std::unique_ptr<Core> core = std::make_unique<Core>();
    core->run();
    return 0;
}
