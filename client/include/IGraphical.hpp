/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "encapsulation/Raylibcpp.hpp"

class IGraphical {
    public:
        virtual ~IGraphical() = default;
};

class Graphic : public IGraphical {
    public:
        // typedef enum GameScreen {
        //     GAMEPLAY,
        //     MENU,
        // } GameScreen;
        Graphic() {}
        ~Graphic() = default;
        // int getScreen() const { return _screen; }
        // GameScreen getScreen() const { return static_cast<GameScreen>(_screen); }
        // std::unique_ptr<Raylibcpp::Draw> draw;
    protected:
        // std::unique_ptr<Raylibcpp::RayModel> _model;
        // int _screen;
};


#endif /* !IGRAPHICAL_HPP_ */
