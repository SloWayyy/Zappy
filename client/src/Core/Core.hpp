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
    #include "src/Menu/Tuto.hpp"
    #include "src/Menu/Setting.hpp"
    #include "encapsulation/Raylibcpp.hpp"
    #include "DDLoader/DDLoader.hpp"
    #include "sdk/include/ICommunicationModule.hpp"


class Core {
    public:
        Core(int port, std::string ip);
        ~Core() = default;
        void run(void);
    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Menu> _menu;
        std::shared_ptr<Tuto> _tuto;
        std::shared_ptr<Setting> _setting;
        std::shared_ptr<Gameplay> _gameplay;
        Raylibcpp::RayWindow _rayWindow;
        std::shared_ptr<DDLoader<zappy::sdk::ICommunicationModule>> loader;
        std::shared_ptr<zappy::sdk::ICommunicationModule> network;
};

#endif /* !CORE_HPP_ */
