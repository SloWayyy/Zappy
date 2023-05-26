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

class Core {
    public:
        Core();
        void run(void);
        void initPlayer(void);
    protected:
        Map map;
        Window window;
        std::vector<character> characters;
};

#endif /* !CORE_HPP_ */
