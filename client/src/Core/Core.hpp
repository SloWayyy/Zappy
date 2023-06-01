/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Map.hpp"
    #include "src/Gameplay/Gameplay.hpp"
    #include "src/Menu/Menu.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Core {
    public:
        Core();
        ~Core() = default;
        void run(void);
    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Menu> _menu;
        std::shared_ptr<Gameplay> _gameplay;
        Raylibcpp::RayWindow _rayWindow;
};

#endif /* !CORE_HPP_ */
