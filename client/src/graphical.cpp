/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** graphical
*/

#include "graphical.hpp"

graphical::graphical() : map{ 10, 10 }
{
    camera = { 0 };
    pos_x = 10.0f;
    pos_y = 0.0f;
    cubePosition = { pos_x, 0.0f, pos_y };
}

graphical::~graphical()
{
}

void graphical::init()
{
    InitWindow(WIDTH, HEIGHT, "Zappy");
    SetTargetFPS(60);
    setCamera();
    DisableCursor();
}

void graphical::run()
{
    update();
    handleInput();
    draw();
}

void graphical::stop()
{
    CloseWindow();
}

void graphical::draw()
{
    draw_all_players();
    map.draw();
}

void graphical::setCamera()
{
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 10.0f, 2.0f, 10.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
}

void graphical::update()
{
    UpdateCamera(&camera, 1);
}

void graphical::setCameraPosition(float x, float y, float z)
{
    camera.position = (Vector3){ x, y, z };
}

void graphical::handleInput()
{
    if (IsKeyDown('Z'))
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
}

void graphical::draw_all_players()
{
    for (auto player : players)
        player.draw();
}