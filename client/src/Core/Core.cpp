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

void Core::handleInput(const std::string &command)
{
    std::cout << command << std::endl;
    std::string tmp = command;
    std::string delimiter = " ";
    std::string token;
    std::vector<std::string> args;

    while ((token = tmp.substr(0, tmp.find(delimiter))) != tmp) {
        args.push_back(token);
        tmp.erase(0, tmp.find(delimiter) + delimiter.length());
    }
    args.push_back(tmp);
    if (args[0] == "msz") {
        this->_gameplay->getMap()->setWidth(std::stoi(args[1]));
        this->_gameplay->getMap()->setHeight(std::stoi(args[2]));
    } else if (args[0] == "bct") {
        std::cout << std::stoi(args[1]) << std::stoi(args[2]) << std::stoi(args[3]) << std::stoi(args[4]) << std::stoi(args[5]) << std::stoi(args[6]) << std::stoi(args[7]) << std::stoi(args[8]) << std::stoi(args[9]) << std::endl;
    } else if (args[0] == "tna") {
        std::cout << args[1] << std::endl;
    } else if (args[0] == "pnw") {
        this->_gameplay->initPlayer({std::stof(args[2]) * 4.0f, (float)1.1, std::stof(args[3]) * 4.0f}, std::stoi(args[5]), std::stoi(args[4]), std::stoi(args[1]), args[6]);
    } else if (args[0] == "ppo") {
        this->_gameplay->getCharacters()[std::stoi(args[1])].setPos(std::stof(args[2]) * 4.0f, std::stof(args[3]) * 4.0f, std::stof(args[4]) * 4.0f);
    } else if (args[0] == "plv") {
        this->_gameplay->getCharacters()[std::stoi(args[1])].setLevel(std::stoi(args[2]));
    } else if (args[0] == "pin") {
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setFood(std::stoi(args[4]));
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setLinemate(std::stoi(args[5]));
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setDeraumere(std::stoi(args[6]));
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setSibur(std::stoi(args[7]));
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setMendiane(std::stoi(args[8]));
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setPhiras(std::stoi(args[9]));
        this->_gameplay->getCharacters()[std::stoi(args[1])].getInventory().setThystame(std::stoi(args[10]));
    } else if (args[0] == "pdi") {
        this->_gameplay->getCharacters().erase(std::stoi(args[1]));
    }
}