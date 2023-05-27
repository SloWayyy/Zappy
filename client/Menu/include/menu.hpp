/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "IGraphical.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Menu : public Raylibcpp::Draw {
    public:
        Menu();
        ~Menu() = default;
        void init();
        void run();
        void stop();
        void draw();
        void handleInput();
    private:
        Texture2D _background;
        // Raylibcpp::RayModel::modelType _type;
        // unsigned int _animsCount;
        // int _animFrameCounter;
        // Vector3 _position;
        // Model _model;
        // Texture2D _texture;
};

#endif /* !MENU_HPP_ */
