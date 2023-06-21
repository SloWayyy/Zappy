/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#include "src/Core/Window.hpp"

Window::Window(std::size_t height, std::size_t width, std::size_t fps) : _windowParam{height, width, fps}, _isExit(false), _gameEvent(GameEvent::MENU), _isNight(false), _isChanged(false)
{
    try {
        this->_rayWindow.initWindow(this->_windowParam._screenHeight, this->_windowParam._screenWidth, "Zappy");
        this->_rayWindow.setTargetFPS(this->_windowParam._fps);
        this->_rayMusic.initAudioDevice();
        this->_musics.insert(std::make_pair(1, this->_rayMusic.loadMusicStream("client/assets/song/gameSong.mp3")));
        this->_musics.insert(std::make_pair(2, this->_rayMusic.loadMusicStream("client/assets/song/music2.mp3")));
        this->_sound = this->_raySound.loadSound("client/assets/song/ButtonSound.wav");
        this->_raySound.setSoundVolume(this->_sound, 0.5f);
        this->setMusic(this->_musics[1]);
        this->_rayMusic.playMusicStream(this->_music);
        this->_rayMusic.setMusicVolume(this->_music, 0.05f);
        this->_clock = 0;
        this->_coefx = 1.0f;
        this->_coefy = 1.0f;
        this->setDefaultCamera();
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        exit (84);
    }
}

Window::~Window()
{
    for (auto &it : this->_musics)
        this->_rayMusic.unloadMusicStream(it.second);
    this->_raySound.unloadSound(this->_sound);
    this->_rayMusic.closeAudioDevice();
}

void Window::setMusic(Music _music)
{
    this->_music = _music;
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
    if (this->_rayWindow.isKeyPressed(KEY_ESCAPE) || this->_rayWindow.windowShouldClose())
        this->_gameEvent = GameEvent::EXIT;
}

void Window::run()
{
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

void Window::setClock(double clock)
{
    this->_clock = clock;
}

double Window::getClock(void) const
{
    return (this->_clock);
}

void Window::setIsNight(bool isNight)
{
    this->_isNight = isNight;
}

bool Window::getIsNight(void) const
{
    return (this->_isNight);
}

void Window::setIsChanged(bool isChanged)
{
    this->_isChanged = isChanged;
}

bool Window::getIsChanged(void) const
{
    return (this->_isChanged);
}
void Window::setCoefx(int coefx)
{
    _coefx = 10.0f / coefx * 1.0f;
}

void Window::setCoefy(int coefy)
{
    _coefy = 10.0f / coefy * 1.0f;
}

void Window::setKeyCam1(std::size_t key)
{
    this->key_cam1 = key;
}

void Window::setKeyCam2(std::size_t key)
{
    this->key_cam2 = key;
}

void Window::setKeyCam3(std::size_t key)
{
    this->key_cam3 = key;
}

std::size_t Window::getKeyCam1(void) const
{
    return (this->key_cam1);
}

std::size_t Window::getKeyCam2(void) const
{
    return (this->key_cam2);
}

std::size_t Window::getKeyCam3(void) const
{
    return (this->key_cam3);
}

std::string Window::keyToString(std::size_t const &key)
{
    std::string os;

    if (key == KEY_F1)
        os = "F1";
    if (key == KEY_F2)
        os = "F2";
    if (key == KEY_F3)
        os = "F3";
    if (key == KEY_X)
        os = "X";
    if (key == KEY_C)
        os = "C";
    if (key == KEY_V)
        os = "V";
    if (key == KEY_K)
        os = "K";
    if (key == KEY_L)
        os = "L";
    if (key == KEY_F)
        os = "F";
    return os;
}

std::map<std::size_t, Music> Window::getMusics(void) const
{
    return (this->_musics);
}

std::size_t Window::getTick(void) const
{
    return (this->_tick);
}

void Window::setTick(std::size_t tick)
{
    this->_tick = tick;
}

void Window::setWriteBuffer(std::string const &writeBuffer)
{
    this->_writeBuffer = writeBuffer;
}

std::string Window::getWriteBuffer(void) const
{
    return (this->_writeBuffer);
}

Sound Window::getSound(void) const
{
    return (this->_sound);
}