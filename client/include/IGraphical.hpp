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

class graphic : public IGraphical
{
    typedef enum GameScreen {
        GAMEPLAY,
    } GameScreen;
    public:
        graphic();
        std::unique_ptr<Raylibcpp::Draw> draw;
    protected:
        std::unique_ptr<Raylibcpp::RayModel> _model;
};


#endif /* !IGRAPHICAL_HPP_ */
