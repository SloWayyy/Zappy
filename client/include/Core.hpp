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
    #include "Window.hpp"
    #include "Map.hpp"
    #include "Gameplay.hpp"
    #include "Character.hpp"
    #include "Menu/include/Menu.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Core : public Raylibcpp::Draw {
    public:
        Core();
        ~Core() = default;
        void run(void);
    protected:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Menu> _menu;
        std::shared_ptr<Gameplay> _gameplay;
        Raylibcpp::RayWindow _rayWindow;
};

#endif /* !CORE_HPP_ */
