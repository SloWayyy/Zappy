/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#include "window.hpp"

Window::Window(int height, int width, int fps)
{
    this->_windowParam._screenWidth = width;
    this->_windowParam._screenHeight = height;
    this->_windowParam._fps = fps;
    this->_isExit = false;
    this->setGameEvent(MENU);
    InitWindow(this->_windowParam._screenHeight, this->_windowParam._screenWidth, "Zappy");
    SetTargetFPS(this->_windowParam._fps);
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
    this->updateCamera();
    this->handleInput();
}
