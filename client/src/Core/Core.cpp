/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#include "src/Core/Core.hpp"
#include <string>
#include <cstring>

Core::Core(int port, std::string ip)
{
    try {
        this->loader = std::make_shared<DDLoader<zappy::sdk::ICommunicationModule>>("client/libs/communication_sdk.so");
        this->network = std::shared_ptr<zappy::sdk::ICommunicationModule>(this->loader->getInstance("communicationEntrypoint"));
        this->network->connect(ip, port);
        this->network->connectAsGraphical();
        this->_window = std::make_shared<Window>(1920, 1080, 60);
        this->_menu = std::make_shared<Menu>(this->_window);
        this->_tuto = std::make_shared<Tuto>(this->_window);
        this->_setting = std::make_shared<Setting>(this->_window);
        this->_gameover = std::make_shared<Gameover>(this->_window);
        this->_gameplay = std::make_shared<Gameplay>(this->_window);
    } catch (const DDLoader<zappy::sdk::ICommunicationModule>::DDLException &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Error: Cannot load communication module");
    } catch (const zappy::sdk::CommunicationException &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Error: Cannot connect to server");
    } catch (const AScreen::Error &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Error: Cannot load raylib");
    } catch (const Gameplay::Error &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Error: Cannot load gameplay");
    }
}

void Core::run(void)
{
    while (!this->_window->getExit()) {
        this->_rayWindow.clearBackground(SKYBLUE);
        this->_rayWindow.beginDrawing();
        auto i = this->network->readBuffer();
        for (auto &command : i) {
            this->handleInput(command);
        }
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
            case GAMEOVER:
                this->_window->run();
                this->_gameover->run();
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
    std::map<std::string, void (Core::*)(std::vector<std::string> &)> commands = {
        {COMMAND_MSZ, &Core::setMapSize},
        {COMMAND_BCT, &Core::setTileContent},
        {COMMAND_TNA, &Core::setTeamNames},
        {COMMAND_PNW, &Core::createNewPosition},
        {COMMAND_PPO, &Core::setPlayerPosition},
        {COMMAND_PLV, &Core::setPlayerLevel},
        {COMMAND_PIN, &Core::setPlayerInventory},
        {COMMAND_PDI, &Core::setPlayerDeath},
        {COMMAND_ENW, &Core::createNewEgg},
        {COMMAND_EBO, &Core::destroyEgg},
        {COMMAND_EDI, &Core::destroyEgg},
        {COMMAND_PBC, &Core::setBroadcast},
        {COMMAND_SEG, &Core::setWinner}
    };

    while ((token = tmp.substr(0, tmp.find(delimiter))) != tmp) {
        args.push_back(token);
        tmp.erase(0, tmp.find(delimiter) + delimiter.length());
    }
    args.push_back(tmp);
    if (commands.find(args[0]) != commands.end())
        (this->*commands[args[0]])(args);

}

void Core::setMapSize(std::vector<std::string> &args)
{
    this->_gameplay->getMap()->setWidth(std::stoi(args[1]));
    this->_gameplay->getMap()->setHeight(std::stoi(args[2]));
    this->_window->setCoefx(std::stoi(args[1]));
    this->_window->setCoefy(std::stoi(args[2]));
}

void Core::setTileContent(std::vector<std::string> &args)
{
    std::array <int, 7> inventory = {std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]), std::stoi(args[7]), std::stoi(args[8]), std::stoi(args[9])};

    if (this->_gameplay->getMap()->getMapInventory().find({std::stoi(args[1]), std::stoi(args[2])}) != this->_gameplay->getMap()->getMapInventory().end()) {
        this->_gameplay->getMap()->getMapInventory()[{std::stoi(args[1]), std::stoi(args[2])}] = inventory;
    } else {
        this->_gameplay->getMap()->getMapInventory().insert({{std::stoi(args[1]), std::stoi(args[2])}, inventory});
    }
}

void Core::setTeamNames(std::vector<std::string> &args)
{
    std::cout << args[1] << std::endl;
}

void Core::createNewPosition(std::vector<std::string> &args)
{
    this->_gameplay->initPlayer({std::stof(args[2]) * 4.0f, (float)1.1, std::stof(args[3]) * 4.0f}, std::stoi(args[5]), std::stoi(args[4]), std::stoi(args[1]), args[6], this->_gameplay->getTextures(), this->_gameplay->getAnimations());
}

void Core::setPlayerPosition(std::vector<std::string> &args)
{
    if (this->_gameplay->getCharacters().find(std::stoi(args[1])) == this->_gameplay->getCharacters().end())
        return; 
    this->_gameplay->getCharacters()[std::stoi(args[1])]->setPos(std::stof(args[2]) * 4.0f, std::stof(args[3]) * 4.0f, std::stof(args[4]));
}

void Core::setPlayerLevel(std::vector<std::string> &args)
{
    if (this->_gameplay->getCharacters().find(std::stoi(args[1])) == this->_gameplay->getCharacters().end())
        return;
    this->_gameplay->getCharacters()[std::stoi(args[1])]->setLevel(std::stoi(args[2]));
}

void Core::setPlayerInventory(std::vector<std::string> &args)
{
    if (this->_gameplay->getCharacters().find(std::stoi(args[1])) == this->_gameplay->getCharacters().end())
        return;
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setFood(std::stoi(args[4]));
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setLinemate(std::stoi(args[5]));
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setDeraumere(std::stoi(args[6]));
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setSibur(std::stoi(args[7]));
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setMendiane(std::stoi(args[8]));
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setPhiras(std::stoi(args[9]));
    this->_gameplay->getCharacters()[std::stoi(args[1])]->getInventory()->setThystame(std::stoi(args[10]));
}

void Core::setPlayerDeath(std::vector<std::string> &args)
{
    if (this->_gameplay->getCharacters().find(std::stoi(args[1])) == this->_gameplay->getCharacters().end())
        return;
    this->_gameplay->getCharacters().erase(std::stoi(args[1]));
}

void Core::setWinner(std::vector<std::string> &args)
{
    std::cout << args[1] << std::endl; 
    this->_window->setGameEvent(GAMEOVER);
}

void Core::createNewEgg(std::vector<std::string> &args)
{
    this->_gameplay->initEgg(std::stoi(args[1]), std::stof(args[2]) * 4.0f, std::stof(args[3]) * 4.0f);
}

void Core::destroyEgg(std::vector<std::string> &args)
{
    if (this->_gameplay->getEggs().find(std::stoi(args[1])) == this->_gameplay->getEggs().end())
        return;
    this->_gameplay->getEggs().erase(std::stoi(args[1]));
}

void Core::setBroadcast(std::vector<std::string> &args)
{
    if (this->_gameplay->getCharacters().find(std::stoi(args[1])) == this->_gameplay->getCharacters().end())
        return;
    this->_gameplay->getCharacters()[std::stoi(args[1])]->setBroadMessage(args[2]);
}
