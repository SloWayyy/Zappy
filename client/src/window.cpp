/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#include <raylib.h>
#include "window.hpp"

Window::Window()
{
    this->_screenWidth = 1920;
    this->_screenHeight = 1080;
    this->_fps = 60;
}

void Window::createWindow(int screenHeight, int screenWidth, int fps)
{
    this->_screenHeight = screenHeight;
    this->_screenWidth = screenWidth;
    this->_fps = fps;

    InitWindow(this->_screenHeight, this->_screenWidth, "Zappy");
    SetTargetFPS(this->_fps);
    setCamera();
    DisableCursor();
}

void Window::setCamera()
{
    this->_camera.position = (Vector3){ 0.0f, 10.0f, 10.0f }; // Camera position
    this->_camera.target = (Vector3){ 10.0f, 2.0f, 10.0f };      // Camera looking at point
    this->_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    this->_camera.fovy = 45.0f;                                // Camera field-of-view Y
    this->_camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
}

void Window::updateCamera()
{
    UpdateCamera(&this->_camera, 1);
}

void Window::setCameraPosition(float x, float y, float z)
{
    this->_camera.position = (Vector3){ x, y, z };
}

void Window::handleInput()
{
    if (IsKeyDown('Z'))
        this->_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
//     if (IsKeyDown(KEY_W))
//         this->_camera.position.z += 0.2f;
//     if (IsKeyDown(KEY_S))
//         this->_camera.position.z -= 0.2f;
//     if (IsKeyDown(KEY_A))
//         this->_camera.position.x -= 0.2f;
//     if (IsKeyDown(KEY_D))
//         this->_camera.position.x += 0.2f;
//     if (IsKeyDown(KEY_Q))
//         this->_camera.position.y -= 0.2f;
//     if (IsKeyDown(KEY_E))
//         this->_camera.position.y += 0.2f;
}

void Window::run()
{
    updateCamera();
    handleInput();
}
