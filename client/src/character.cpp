/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#include "character.hpp"
#include "IGraphical.hpp"

character::character(Raylibcpp::RayModel::modelType type, unsigned int animsCount, int animFrameCounter, Vector3 pos)
{
    this->_position = pos;
    this->_type = type;
    this->_animsCount = animsCount;
    this->_animFrameCounter = animFrameCounter;
    this->_model = LoadModel("assets/monster.obj");
    this->_texture = LoadTexture("assets/monster/monster2.png");
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
}

void character::draw()
{
    drawRayModel(this->_model, this->_position, 0.01f);
}

void character::handleInput()
{
}

void character::stop()
{
    UnloadModel(this->_model);
}


void character::run()
{
    this->draw();
    this->handleInput();
}
