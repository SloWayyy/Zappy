/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#include "Window.hpp"

Window::Window(int height, int width, int fps)
{
    this->_windowParam._screenWidth = width;
    this->_windowParam._screenHeight = height;
    this->_windowParam._fps = fps;
    this->_isExit = false;
    this->setGameEvent(MENU);
    InitWindow(this->_windowParam._screenHeight, this->_windowParam._screenWidth, "Zappy");
    SetTargetFPS(this->_windowParam._fps);
    // this->setCamera({ -11.0f, 14.0f, 8.0f }, { 8.0f, 0.0f, 10.0f }, { 0.9f, 0.5f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
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
    printf("Camera position: %f %f %f\n", this->_camera.position.x, this->_camera.position.y, this->_camera.position.z);
    printf("Camera target: %f %f %f\n", this->_camera.target.x, this->_camera.target.y, this->_camera.target.z);
    printf("Camera up: %f %f %f\n", this->_camera.up.x, this->_camera.up.y, this->_camera.up.z);
    printf("Camera fovy: %f\n", this->_camera.fovy);
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

void Window::setGameEvent(GameEvent event)
{
    this->_gameEvent = event;
}

GameEvent Window::getGameEvent(void) const
{
    return (this->_gameEvent);
}

std::size_t Window::getScreenHeight(void) const
{
    return (this->_windowParam._screenHeight);
}

std::size_t Window::getScreenWidth(void) const
{
    return (this->_windowParam._screenWidth);
}

std::size_t Window::getFps(void) const
{
    return (this->_windowParam._fps);
}

void Window::setExit(bool exit)
{
    this->_isExit = exit;
}

bool Window::getExit(void) const
{
    return (this->_isExit);
}

Camera Window::getCamera() const
{
    return (this->_camera);
}
