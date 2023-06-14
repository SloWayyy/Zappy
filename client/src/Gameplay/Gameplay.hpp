/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#ifndef GAMEPLAY_HPP_
    #define GAMEPLAY_HPP_

    #include <memory>
    #include <map>
    #include <vector>
    #include "src/Gameplay/Map.hpp"
    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Character.hpp"
    #include "src/Gameplay/Egg.hpp"
    #include "src/Gameplay/Display.hpp"
    #include "encapsulation/Raylibcpp.hpp"

enum CameraType {
    CAMERA_FIRST,
    CAMERA_SECOND,
    CAMERA_THIRD
};

class Gameplay {
    public:
        class Error : public std::exception {
            public:
                Error(std::string const &message) : _message(message) {};
                ~Error() = default;
                const char *what() const noexcept override { return _message.c_str(); }
            private:
                std::string _message;
        };
        Gameplay(std::shared_ptr<Window> _window);
        ~Gameplay() = default;
        void run(void);
        void initPlayer(Vector3 pos, std::size_t level, std::size_t orientation, std::size_t id, std::string teamname, std::map<std::size_t, Texture2D>);
        void initEgg(std::size_t id, float x, float y);
        void runPlayers(void);
        void runEggs(void);
        void handleInput(void);
        void drawMap(void);
        void drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color);
        void setCurrentCharacter();
        void startAnimation();
        void DisplayInformations();
        void setDisplayMode();
        void setIsDisplay(bool isDisplay);
        void setCameraType(CameraType cameraType);
        CameraType getCameraType(void) const;
        std::shared_ptr<Map> getMap() const;
        std::map<std::size_t, Texture2D> getTextures() const;
        void setTextures();
        std::map<std::size_t, std::shared_ptr<Character>> &getCharacters();
        std::map<std::size_t, std::shared_ptr<Egg>> &getEggs();
    private:
        std::shared_ptr<Window> _window;
        Display _display;
        std::shared_ptr<Map> _map;
        std::map<std::size_t, std::shared_ptr<Character>> _characters;
        std::map<std::size_t, std::shared_ptr<Egg>> _eggs;
        std::size_t _currentCharacterId;
        std::size_t _currentCharacterIndex;
        std::shared_ptr<Character> _currentCharacter;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayCube _rayCube;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayText _rayText;
        bool _isDisplay;
        CameraType _cameraType;
        std::map<std::size_t, Texture2D> _textures;
};

#endif /* !GAMEPLAY_HPP_ */
