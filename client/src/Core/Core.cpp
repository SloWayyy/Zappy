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
    (void)port;
    (void)ip;
    try {
        this->loader = std::make_shared<DDLoader<zappy::sdk::ICommunicationModule>>("libs/communication_sdk.so");
        this->network = std::shared_ptr<zappy::sdk::ICommunicationModule>(this->loader->getInstance("communicationEntrypoint"));
        this->network->connect(ip, port);
        this->network->connectAsGraphical();
    } catch (const DDLoader<zappy::sdk::ICommunicationModule>::DDLException &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Error: Cannot load communication module");
    } catch (const zappy::sdk::CommunicationException &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Error: Cannot connect to server");
    }
}

void Core::run(void)
{
    while (!this->_window->getExit()) {
        this->_rayWindow.clearBackground(this->_window->getColorBackground());
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
    }
}

Core::CoreException::CoreException(std::string const &message): _message(message)
{
}

const char *Core::CoreException::what() const noexcept
{
    return this->_message.c_str();
}