/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Egg.cpp
*/

#include "src/Gameplay/Egg.hpp"

Egg::Egg(std::size_t id, float x, float y)
{
    this->_id = id;
    this->_position = {x, 1.1f, y};
}

std::size_t Egg::getId() const
{
    return this->_id;
}

Vector3 Egg::getPosition() const
{
    return this->_position;
}

void Egg::run(void)
{
    // draw the model 3D here
}
