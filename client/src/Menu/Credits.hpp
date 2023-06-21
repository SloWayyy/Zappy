/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Credits.hpp
*/

#ifndef CREDITS_HPP_
    #define CREDITS_HPP_

    #include "AScreen.hpp"

class Credits : public AScreen {
    public:
        Credits(std::shared_ptr<Window> window);
        ~Credits();
    private:
        void handleInput(void) override;
        Texture2D _mixamo;
        Texture2D _blender;
        Texture2D _sketchfab;
        std::size_t width;
        std::size_t height;
};

#endif /* !CREDITS_HPP_ */