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
    #include "gameplay.hpp"
    #include "character.hpp"
    #include "Menu/include/menu.hpp"

class Core : public Raylibcpp::Draw {
    public:
        Core();
        ~Core() = default;
        void run(void);
    protected:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Gameplay> _gameplay;
        std::shared_ptr<Menu> _menu;
};

#endif /* !CORE_HPP_ */
