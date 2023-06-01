/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include "encapsulation/Raylibcpp.hpp"

enum GameEvent {
    MENU,
    GAMEPLAY,
    SETTINGS,
    TUTO,
    EXIT
};

struct windowParams {
    std::size_t _screenHeight;
    std::size_t _screenWidth;
    std::size_t _fps;
};

class Window {
    public:
        Window() = default;
        Window(std::size_t height, std::size_t width, std::size_t fps);
        ~Window() = default;
        void run();
        void updateCamera();
        void handleInput();
        void setGameEvent(GameEvent event);
        void setCamera(Vector3 pos, Vector3 target, Vector3 up, float fovy, int projection);
        Camera getCamera() const;
        GameEvent getGameEvent(void) const;
        std::size_t getScreenHeight(void) const;
        std::size_t getScreenWidth(void) const;
        std::size_t getFps(void) const;
        void setExit(bool exit);
        bool getExit(void) const;
    private:
        windowParams _windowParam;
        bool _isExit;
        GameEvent _gameEvent;
        Camera _camera;
        Raylibcpp::RayWindow _rayWindow;
};

#endif /* !WINDOW_HPP_ */
