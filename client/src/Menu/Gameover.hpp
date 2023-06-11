/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gameover
*/

#ifndef GAMEOVER_HPP_
    #define GAMEOVER_HPP_

    #include "AScreen.hpp"

class Gameover : public AScreen {
    public:
        Gameover(std::shared_ptr<Window> window);
        ~Gameover() = default;
    private:
        void handleInput() override;
};

#endif /* !GAMEOVER_HPP_ */
