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
    this->setCamera({ 0.0f, 10.0f, 10.0f }, { 10.0f, 2.0f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
}

void Window::setCamera(Vector3 pos, Vector3 target, Vector3 up, float fovy, int projection)
{
    this->_camera.position = pos;
    this->_camera.target = target;
    this->_camera.up = up;
    this->_camera.fovy = fovy;
    this->_camera.projection = projection;
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
    // if (IsKeyPressed(KEY_F1))
    //     this->setCamera({ 0.0f, 2.0f, 2.0f }, { 10.0f, 2.0f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
}

void Window::run()
{
    this->updateCamera();
    this->handleInput();
}
