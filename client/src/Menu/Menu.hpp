/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "AScreen.hpp"

class Menu : public AScreen {
    public:
        Menu(std::shared_ptr<Window> window);
        ~Menu() = default;
    private:
        void handleInput() override;
};

#endif /* !MENU_HPP_ */
