/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#ifndef GAMEPLAY_HPP_
    #define GAMEPLAY_HPP_

    #include <memory>
    #include "src/Gameplay/Map.hpp"
    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Character.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Gameplay {
    public:
        Gameplay(std::shared_ptr<Window> _window);
        ~Gameplay() = default;
        void run(void);
        void initPlayer(Vector3 pos);
        void runPlayers(void);
        void handleInput(void);
        void drawMap(void);
        void findPlayer(void);
        void drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color);
        void setCurrentCharacter();
    private:
        std::shared_ptr<Window> _window;
        Map _map;
        std::vector<Character> _characters;
        std::size_t _currentCharacterId;
        std::size_t _currentCharacterIndex;
        Character _currentCharacter;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayCube _rayCube;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayText _rayText;
};

#endif /* !GAMEPLAY_HPP_ */
