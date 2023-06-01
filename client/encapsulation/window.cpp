/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::RayWindow::initWindow(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void Raylibcpp::RayWindow::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

bool Raylibcpp::RayWindow::isKeyDown(int key)
{
    return IsKeyDown(key);
}

bool Raylibcpp::RayWindow::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

bool Raylibcpp::RayWindow::isKeyReleased(int key)
{
    return IsKeyReleased(key);
}

void Raylibcpp::RayWindow::beginDrawing()
{
    BeginDrawing();
}

void Raylibcpp::RayWindow::endDrawing()
{
    EndDrawing();
}

void Raylibcpp::RayWindow::clearBackground(Color color)
{
    ClearBackground(color);
}

void Raylibcpp::RayWindow::beginMode3D(Camera3D camera)
{
    BeginMode3D(camera);
}

void Raylibcpp::RayWindow::endMode3D()
{
    EndMode3D();
}
