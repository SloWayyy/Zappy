/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Egg.cpp
*/

#include "src/Gameplay/Egg.hpp"

Egg::Egg(std::size_t id, float x, float y, Model model, Texture texture)
{
    this->_id = id;
    this->_position = {x, 1.9f, y};
    this->_model = model;
    this->_texture = texture;
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
    this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
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
    this->_rayModel.drawModel(this->_model, this->_position, 0.5f, WHITE);
}
