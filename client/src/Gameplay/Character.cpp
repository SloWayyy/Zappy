/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#include "encapsulation/Raylibcpp.hpp"
#include "raymath.h"
#include "src/Gameplay/Character.hpp"

Character::Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos) : _position(pos), _animsCount(animsCount), _animFrameCounter(animFrameCounter)
{
    this->_model = this->_rayModel.loadModel("assets/monster/woody.iqm");
    this->_texture = this->_rayModel.loadTexture("assets/monster/woody.png");
    this->_anims = this->_rayModel.loadModelAnimations("assets/monster/woodyRun.iqm", &this->_animsCount);
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
}

void Character::animation()
{
    this->_rayModel.updateModelAnimation(this->_model, this->_anims[0], this->_animFrameCounter);
    this->_animFrameCounter++;
    if (this->_animFrameCounter >= this->_anims[0].frameCount)
        this->_animFrameCounter = 0;
}

void Character::draw()
{
    this->_rayModel.drawModel(this->_model, this->_position, 0.1f, WHITE);
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