/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** IScreen
*/

#ifndef ISCREEEN_HPP_
    #define ISCREEEN_HPP_

    #include <raylib.h>
    #include <vector>
    #include "../Core/Window.hpp"
    #include "../Gameplay/Map.hpp"
    #include "../Gameplay/Gameplay.hpp"
    #include "Button.hpp"
    #include "encapsulation/Raylibcpp.hpp"


class IScreen {
    public:
        ~IScreen() = default;
        virtual void run(void) = 0;
        virtual void draw(void) = 0;
        virtual void handleInput(void) = 0;
        virtual void createButtons(std::string string, coord coord, Color color, int size, GameEvent screen) = 0;
        virtual void drawButton(void) = 0;
};

#endif /* !ISCREEEN_HPP_ */
