/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <chrono>
    #include <map>
    #include "encapsulation/Raylibcpp.hpp"

enum GameEvent {
    MENU,
    GAMEPLAY,
    SETTINGS,
    TUTO,
    GAMEOVER,
    DISCONNECT,
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
        ~Window();
        void run();
        void updateCamera();
        void handleInput();
        void setGameEvent(GameEvent event);
        void setMusic(Music _music);
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
        std::map<std::size_t, Music> getMusics(void) const;
        double getClock(void) const;
        void setClock(double clock);
        void setIsNight(bool isNight);
        bool getIsNight(void) const;
        void setIsChanged(bool isChanged);
        bool getIsChanged(void) const;
        void setCoefx(int coefx);
        void setCoefy(int coefy);
        void setKeyCam1(std::size_t key);
        void setKeyCam2(std::size_t key);
        void setKeyCam3(std::size_t key);
        std::size_t getKeyCam1(void) const;
        std::size_t getKeyCam2(void) const;
        std::size_t getKeyCam3(void) const;
        std::string keyToString(std::size_t const &key);
        std::size_t getTick(void) const;
        void setTick(std::size_t tick);
        void setWriteBuffer(std::string const &writeBuffer);
        std::string getWriteBuffer(void) const;
        Sound getSound(void) const;
        void setWinningTeam(std::string const &winningteam);
        std::string getWinningTeam(void) const;
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
        std::size_t key_cam1 = KEY_F1;
        std::size_t key_cam2 = KEY_F2;
        std::size_t key_cam3 = KEY_F3;
        std::map<std::size_t, Music> _musics;
        std::size_t _tick = 0;
        std::string _writeBuffer;
        Raylibcpp::RaySound _raySound;
        Sound _sound;
        std::string _winningteam;
        std::chrono::steady_clock::time_point _startTime;
        std::chrono::steady_clock::time_point _currentTime;
        std::chrono::duration<double> _elapsedSeconds;
};

#endif /* !WINDOW_HPP_ */
