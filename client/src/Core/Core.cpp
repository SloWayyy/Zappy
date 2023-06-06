/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#include "src/Core/Core.hpp"
#include <string>
#include <cstring>

Core::Core(int port, std::string ip): _window(std::make_shared<Window>(1920, 1080, 60)), _menu(std::make_shared<Menu>(this->_window)), _tuto(std::make_shared<Tuto>(this->_window)), _setting(std::make_shared<Setting>(this->_window)) , _gameplay(std::make_shared<Gameplay>(this->_window))
{
    this->_network = std::make_shared<Network>(port, ip);
    _network->connectToServer();
}

void Core::run(void)
{
    while (!this->_window->getExit()) {
        _network->set_fd();
        _network->select_socket();
        _network->GetresponseFromServer();
        // std::cout << _network->getBuffer() << std::endl;
        this->_rayWindow.clearBackground(RAYWHITE);
        this->_rayWindow.beginDrawing();
        switch (this->_window->getGameEvent()) {
            case MENU:
                this->_window->run();
                this->_menu->run();
                break;
            case GAMEPLAY:
                this->_rayWindow.beginMode3D(this->_window->getCamera());
                this->_window->run();
                this->_gameplay->run();
                this->_rayWindow.endMode3D();
                break;
            case SETTINGS:
                this->_window->run();
                this->_setting->run();
                break;
            case TUTO:
                this->_window->run();
                this->_tuto->run();
                break;
            case EXIT:
                this->_window->setExit(true);
        }
        this->_rayWindow.endDrawing();
        _network->getBuffer().clear();
    }
}
