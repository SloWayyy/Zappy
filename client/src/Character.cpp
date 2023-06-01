/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#include "encapsulation/Raylibcpp.hpp"
#include "raymath.h"
#include "Character.hpp"

Character::Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos)
{
    this->_position = pos;
    this->_animsCount = animsCount;
    this->_animFrameCounter = animFrameCounter;
    this->_model = LoadModel("assets/monster/woody.iqm");
    this->_texture = LoadTexture("assets/monster/woody.png");
    this->_anims = LoadModelAnimations("assets/monster/woodyRun.iqm", &this->_animsCount);
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
}

void Character::animation()
{
    UpdateModelAnimation(this->_model, this->_anims[0], this->_animFrameCounter);
    this->_animFrameCounter++;
    if (this->_animFrameCounter >= this->_anims[0].frameCount)
        this->_animFrameCounter = 0;
}

void Character::draw()
{
    DrawModel(this->_model, this->_position, 0.1f, WHITE);
    this->_model.transform = MatrixRotateXYZ({-90, 0, 0});
}

void Character::run()
{
    this->draw();
    this->animation();
}

Vector3 Character::getPosition() const
{
    return this->_position;
}