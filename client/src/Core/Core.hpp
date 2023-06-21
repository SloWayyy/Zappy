/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #define COMMAND_MSZ "msz"
    #define COMMAND_BCT "bct"
    #define COMMAND_TNA "tna"
    #define COMMAND_PNW "pnw"
    #define COMMAND_PPO "ppo"
    #define COMMAND_PLV "plv"
    #define COMMAND_PIN "pin"
    #define COMMAND_PDI "pdi"
    #define COMMAND_SEG "seg"
    #define COMMAND_ENW "enw"
    #define COMMAND_EBO "ebo"
    #define COMMAND_EDI "edi"
    #define COMMAND_PBC "pbc"
    #define COMMAND_PIC "pic"
    #define COMMAND_PIE "pie"
    #define COMMAND_SMG "smg"
    #define COMMAND_ENI "eni"
    #define COMMAND_PDR "pdr"
    #define COMMAND_SGT "sgt"
    #define COMMAND_SST "sst"
    #define SERVER_DISCONNECT "disconnect"

    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Map.hpp"
    #include "src/Gameplay/Gameplay.hpp"
    #include "src/Menu/Menu.hpp"
    #include "src/Menu/Tuto.hpp"
    #include "src/Menu/Gameover.hpp"
    #include "src/Menu/Disconnect.hpp"
    #include "src/Menu/Setting.hpp"
    #include "encapsulation/Raylibcpp.hpp"
    #include "DDLoader/DDLoader.hpp"
    #include "ICommunicationModule.hpp"


class Core {
    public:
        class CoreException : public std::exception {
            public:
                CoreException(std::string const &message);
                const char *what() const noexcept override;
            private:
                std::string _message;
        };
        Core(int port, std::string ip);
        ~Core() = default;
        void run(void);
        void handleInput(const std::string &input);
        void setMapSize(std::vector<std::string> &input);
        void setTileContent(std::vector<std::string> &input);
        void setTeamNames(std::vector<std::string> &input);
        void createNewPosition(std::vector<std::string> &input);
        void setPlayerPosition(std::vector<std::string> &input);
        void setPlayerLevel(std::vector<std::string> &input);
        void setPlayerInventory(std::vector<std::string> &input);
        void setPlayerDeath(std::vector<std::string> &input);
        void setWinner(std::vector<std::string> &input);
        void createNewEgg(std::vector<std::string> &input);
        void destroyEgg(std::vector<std::string> &input);
        void setBroadcast(std::vector<std::string> &input);
        void addIncantation(std::vector<std::string> &input);
        void endIncantation(std::vector<std::string> &input);
        void personnalMessage(std::vector<std::string> &input);
        void dropResource(std::vector<std::string> &input);
        void setTimeUnit(std::vector<std::string> &input);
        void setDisconnectEvent(std::vector<std::string> &input);
        bool checkConnection();
    private:
        int _port;
        std::string _ip;
        std::shared_ptr<Window> _window;
        std::shared_ptr<Menu> _menu;
        std::shared_ptr<Tuto> _tuto;
        std::shared_ptr<Setting> _setting;
        std::shared_ptr<Gameover> _gameover;
        std::shared_ptr<Gameplay> _gameplay;
        std::shared_ptr<Disconnect> _disconnect;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayClock _rayClock;
        std::shared_ptr<DDLoader<zappy::sdk::ICommunicationModule>> loader;
        std::shared_ptr<zappy::sdk::ICommunicationModule> network;
};

#endif /* !CORE_HPP_ */
