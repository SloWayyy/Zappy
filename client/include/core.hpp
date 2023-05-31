/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <raylib.h>
    #include <vector>
    #include "window.hpp"
    #include "Map.hpp"
    #include "character.hpp"
    #include "Menu/include/menu.hpp"

class Core : public Raylibcpp::Draw {
    public:
        Core();
        ~Core() = default;
        void run(void);
        void initPlayer(void);
        void drawPlayers(void);
    protected:
        Map _map;
        Window _window;
        std::vector<character> _characters;
        Menu _menu;
};

#endif /* !CORE_HPP_ */
