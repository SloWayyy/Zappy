/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** graphical
*/

#include "graphical.hpp"

graphical::graphical()
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
    pos_x = 10.0f;
    pos_y = 0.0f;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            Vector3 cubePosition = { pos_x, 0.0f, pos_y };
            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
            DrawGrid(10, 1.0f);
            pos_x += 2.0f;
        }
        pos_x = 10.0f;
        pos_y += 2.0f;
    }
    DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines( 10, 10, 320, 133, BLUE);
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
