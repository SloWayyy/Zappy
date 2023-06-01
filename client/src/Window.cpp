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
    this->_rayWindow.initWindow(this->_windowParam._screenHeight, this->_windowParam._screenWidth, "Zappy");
    this->_rayWindow.setTargetFPS(this->_windowParam._fps);
    // change the fovy to change the vision of camera
    this->setCamera({ -5.0f, 15.0f, 10.0f }, { 10.0f, 2.0f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 80.0f, CAMERA_PERSPECTIVE);
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
    // UpdateCamera(&this->_camera, 1);
}

void Window::handleInput()
{
    if (this->_rayWindow.isKeyDown(KEY_Z))
        this->_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    if (this->_rayWindow.isKeyPressed(KEY_ENTER))
        this->_gameEvent = GameEvent::GAMEPLAY;
    if (this->_rayWindow.isKeyPressed(KEY_P) && (this->_gameEvent == GameEvent::GAMEPLAY))
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
