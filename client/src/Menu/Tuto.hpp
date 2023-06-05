/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tuto
*/

#ifndef TUTO_HPP_
    #define TUTO_HPP_

    #include "AScreen.hpp"

class Tuto : public AScreen {
    public:
        Tuto(std::shared_ptr<Window> window);
        ~Tuto() = default;
    private:
        void handleInput() override;
};

#endif /* !TUTO_HPP_ */
