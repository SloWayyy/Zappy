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
} GameEvent;

class Window {
    public:
        Window();
        void createWindow(int Height, int Width, int fps);
        int getScreenHeight(void) const { return _screenHeight; };
        int getScreenWidth(void) const { return _screenWidth; };
        int getFps(void) const { return _fps; };
        void updateCamera();
        void setCamera();
        void setCameraPosition(float x, float y, float z);
        Camera getCamera() const { return _camera; };
        void handleInput();
        void run();
        void setGameEvent(GameEvent event) { this->_gameEvent = event; };
        GameEvent getGameEvent(void) { return this->_gameEvent; };
    protected:
        GameEvent _gameEvent;
        Camera _camera;
        int _screenHeight;
        int _screenWidth;
        int _fps;
};

#endif /* !WINDOW_HPP_ */
