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
    GAMEOVER,
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
        void setMusic(const std::string &musicPath);
        void setCamera(Vector3 pos, Vector3 target, Vector3 up, float fovy, int projection);
        Camera getCamera() const;
        GameEvent getGameEvent(void) const;
        std::size_t getScreenHeight(void) const;
        std::size_t getScreenWidth(void) const;
        std::size_t getFps(void) const;
        void setScreenHeight(std::size_t height);
        void setScreenWidth(std::size_t width);
        void setFps(std::size_t fps);
        void setExit(bool exit);
        bool getExit(void) const;
        void setDefaultCamera(void);
        Raylibcpp::RayWindow getRayWindow(void) const;
        Music getMusic(void) const;
        double getClock(void) const;
        void setClock(double clock);
        void setIsNight(bool isNight);
        bool getIsNight(void) const;
        void setIsChanged(bool isChanged);
        bool getIsChanged(void) const;
        void setCoefx(int coefx);
        void setCoefy(int coefy);
    private:
        windowParams _windowParam;
        double _clock;
        bool _isExit;
        GameEvent _gameEvent;
        Camera _camera;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayMusic _rayMusic;
        Raylibcpp::RayClock _rayClock;
        Music _music;
        bool _isNight;
        bool _isChanged;
        float _coefx;
        float _coefy;
};

#endif /* !WINDOW_HPP_ */
