/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Disconnect
*/

#ifndef DISCONNECT_HPP_
    #define DISCONNECT_HPP_

    #include "AScreen.hpp"

class Disconnect : public AScreen {
    public:
        Disconnect(std::shared_ptr<Window> window);
        ~Disconnect();
    private:
        void handleInput() override;
};

#endif /* !DISCONNECT_HPP_ */