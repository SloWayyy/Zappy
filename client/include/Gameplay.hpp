/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#ifndef GAMEPLAY_HPP_
    #define GAMEPLAY_HPP_

    #include <memory>
    #include "Map.hpp"
    #include "window.hpp"
    #include "Character.hpp"

class Gameplay {
    public:
        Gameplay(std::shared_ptr<Window> _window);
        ~Gameplay() = default;
        void run(void);
        void initPlayer(Vector3 pos);
        void runPlayers(void);
        void handleInput(void);
        void setCurrentCharacter();
    protected:
    private:
        std::shared_ptr<Window> _window;
        Map _map;
        std::vector<Character> _characters;
        std::size_t _currentCharacterId;
        std::size_t _currentCharacterIndex;
        Character _currentCharacter;
};

#endif /* !GAMEPLAY_HPP_ */
