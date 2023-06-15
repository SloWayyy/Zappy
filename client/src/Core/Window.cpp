/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#include "src/Core/Window.hpp"

Window::Window(std::size_t height, std::size_t width, std::size_t fps) : _windowParam{ height, width, fps }, _isExit(false), _gameEvent(GameEvent::MENU)
{
    try {
        this->_rayWindow.initWindow(this->_windowParam._screenHeight, this->_windowParam._screenWidth, "Zappy");
        this->_rayWindow.setTargetFPS(this->_windowParam._fps);
        this->_rayMusic.initAudioDevice();
        this->setDefaultCamera();
        this->setMusic("client/assets/song/gameSong.mp3");
        this->_colorBackground = SKYBLUE;
        this->_clock = 0;
        _coefx = 1.0f;
        _coefy = 1.0f;
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        exit (84);
    }
}

void Window::setMusic(const std::string &musicPath)
{
    this->_music = this->_rayMusic.loadMusicStream(musicPath);
    this->_rayMusic.playMusicStream(this->_music);
    this->_rayMusic.setMusicVolume(this->_music, 0.5f);
}

void Window::setDefaultCamera(void)
{
    this->setCamera({ 16.55f /  _coefx, 23.63f / _coefx, 44.7f / _coefy}, {16.71f / _coefx, 10.38f / _coefx, 31.53f / _coefy}, { -0.006f, 1.12f, -0.57f }, 80.0f, CAMERA_PERSPECTIVE);
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
    this->_rayWindow.updateCamera(&this->_camera, 1);
    std::cout << "Camera position: " << this->_camera.position.x << ", " << this->_camera.position.y << ", " << this->_camera.position.z << std::endl;
    std::cout << "Camera target: " << this->_camera.target.x << ", " << this->_camera.target.y << ", " << this->_camera.target.z << std::endl;
    std::cout << "Camera up: " << this->_camera.up.x << ", " << this->_camera.up.y << ", " << this->_camera.up.z << std::endl;
    std::cout << std::endl << std::endl;
}

void Window::handleInput()
{
    if (this->_rayWindow.isKeyDown(KEY_Z))
        this->_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    if (this->_rayWindow.isKeyPressed(KEY_ENTER))
        this->_gameEvent = GameEvent::GAMEPLAY;
    if (this->_rayWindow.isKeyPressed(KEY_P)) {
        switch (this->_gameEvent) {
            case GameEvent::GAMEPLAY:
                this->_gameEvent = GameEvent::MENU;
                break;
            case GameEvent::TUTO:
                this->_gameEvent = GameEvent::MENU;
                break;
            case GameEvent::SETTINGS:
                this->_gameEvent = GameEvent::MENU;
                break;
            default:
                break;
        }
    }
    if (this->_rayWindow.isKeyPressed(KEY_ESCAPE))
        this->_gameEvent = GameEvent::EXIT;
}

void Window::run()
{
    // this->_rayMusic.updateMusicStream(this->_music);
    // if ((this->getClock() + 0.005) < this->_rayClock.getTime()) {
    //     this->setClock(this->_rayClock.getTime());
    //     this->updateCamera();
    // }
    // this->handleInput();
    this->_rayMusic.updateMusicStream(this->_music);
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

Raylibcpp::RayWindow Window::getRayWindow(void) const
{
    return (this->_rayWindow);
}

Music Window::getMusic(void) const
{
    return (this->_music);
}

void Window::setScreenHeight(std::size_t height)
{
    this->_windowParam._screenHeight = height;
}

void Window::setScreenWidth(std::size_t width)
{
    this->_windowParam._screenWidth = width;
}

void Window::setFps(std::size_t fps)
{
    this->_windowParam._fps = fps;
}

void Window::setColorBackground(Color color)
{
    this->_colorBackground = color;
}

Color Window::getColorBackground(void) const
{
    return (this->_colorBackground);
}

void Window::setClock(double clock)
{
    this->_clock = clock;
}

double Window::getClock(void) const
{
    return (this->_clock);
}

void Window::setCoefx(int coefx)
{
    _coefx = 10.0f / coefx * 1.0f;
}

void Window::setCoefy(int coefy)
{
    _coefy = 10.0f / coefy * 1.0f;
}