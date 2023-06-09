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
    #include "src/Gameplay/Display.hpp"
    #include "encapsulation/Raylibcpp.hpp"

enum CameraType {
    CAMERA_FIRST,
    CAMERA_SECOND,
    CAMERA_THIRD
};

class Gameplay {
    public:
        Gameplay(std::shared_ptr<Window> _window);
        ~Gameplay() = default;
        void run(void);
        void initPlayer(Vector3 pos, std::size_t level, std::size_t orientation, std::size_t id, std::string teamname);
        void runPlayers(void);
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
    private:
        std::shared_ptr<Window> _window;
        Map _map;
        Display _display;
        std::map<std::size_t, Character> _characters;
        std::size_t _currentCharacterId;
        std::size_t _currentCharacterIndex;
        Character _currentCharacter;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayCube _rayCube;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayText _rayText;
        bool _isDisplay;
        CameraType _cameraType;
};

#endif /* !GAMEPLAY_HPP_ */
