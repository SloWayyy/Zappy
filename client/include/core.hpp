/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include "window.hpp"
#include "Map.hpp"
#include "character.hpp"

class Core : public Raylibcpp::Draw {
    public:
        Core();
        void run(void);
        void initPlayer(void);
        void drawPlayers(void);
    protected:
        Map map;
        Window window;
        std::vector<character> characters;
};

#endif /* !CORE_HPP_ */
