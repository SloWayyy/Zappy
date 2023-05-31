/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include "encapsulation/Raylibcpp.hpp"

typedef enum GameEvent {
    MENU,
    GAMEPLAY,
    SETTINGS,
    TUTO,
    EXIT
} GameEvent;

typedef struct windowParam_s {
    std::size_t _screenHeight;
    std::size_t _screenWidth;
    std::size_t _fps;
} windowParam_t;

class Window {
    public:
        Window() = default;
        Window(int height, int width, int fps);
        ~Window() = default;
        void run();
        void updateCamera();
        void handleInput();
        void setGameEvent(GameEvent event) { this->_gameEvent = event; };
        void setCamera();
        Camera getCamera() const { return _camera; };
        GameEvent getGameEvent(void) const { return this->_gameEvent; };
        std::size_t getScreenHeight(void) const { return _windowParam._screenHeight; };
        std::size_t getScreenWidth(void) const { return _windowParam._screenWidth; };
        std::size_t getFps(void) const { return _windowParam._fps; };
        void setExit(bool exit) { this->_isExit = exit; };
        bool getExit(void) const { return this->_isExit; };
    private:
        GameEvent _gameEvent;
        Camera _camera;
        bool _isExit;
        windowParam_t _windowParam;
};

#endif /* !WINDOW_HPP_ */
