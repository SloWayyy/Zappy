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
    this->setGameEvent(MENU);
}

void Window::createWindow(int screenHeight, int screenWidth, int fps)
{
    this->_screenHeight = screenHeight;
    this->_screenWidth = screenWidth;
    this->_fps = fps;

    InitWindow(this->_screenHeight, this->_screenWidth, "Zappy");
    SetTargetFPS(this->_fps);
    setCamera();
}

void Window::setCamera()
{
    this->_camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    this->_camera.target = (Vector3){ 10.0f, 2.0f, 10.0f };
    this->_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    this->_camera.fovy = 45.0f;
    this->_camera.projection = CAMERA_PERSPECTIVE;
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
    if (IsKeyPressed(KEY_ENTER))
        this->_gameEvent = GameEvent::GAMEPLAY;
    if (IsKeyPressed(KEY_P) && (this->_gameEvent == GameEvent::GAMEPLAY))
        this->_gameEvent = GameEvent::MENU;
}

void Window::run()
{
    updateCamera();
    handleInput();
}
