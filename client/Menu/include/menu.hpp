/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "encapsulation/Raylibcpp.hpp"

class Menu : public Raylibcpp::Draw {
    public:
        Menu();
        ~Menu() = default;
        void init();
        void run();
        void stop();
        void draw();
        void handleInput();
    private:
        Texture2D _background;
};

#endif /* !MENU_HPP_ */
