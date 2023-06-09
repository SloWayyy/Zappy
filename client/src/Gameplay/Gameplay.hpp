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
    #include "src/Gameplay/Map.hpp"
    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Character.hpp"
    #include "encapsulation/Raylibcpp.hpp"

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
        std::shared_ptr<Map> getMap() const;
        std::map<std::size_t, Character> getCharacters() const;
    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Map> _map;
        std::map<std::size_t, Character> _characters;
        std::size_t _currentCharacterId;
        std::size_t _currentCharacterIndex;
        Character _currentCharacter;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayCube _rayCube;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayText _rayText;
};

#endif /* !GAMEPLAY_HPP_ */
