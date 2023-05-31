/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#ifndef GAMEPLAY_HPP_
    #define GAMEPLAY_HPP_

    #include "Map.hpp"
    #include "character.hpp"

class Gameplay {
    public:
        Gameplay();
        ~Gameplay() = default;
        void run(void);
        void initPlayer(void);
        void runPlayers(void);
    protected:
    private:
        Map _map;
        std::vector<character> _characters;
};

#endif /* !GAMEPLAY_HPP_ */
