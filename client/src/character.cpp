/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

// #include "raymath.h"
#include "character.hpp"

character::character(Raylibcpp::RayModel::modelType type, std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos)
{
    this->_position = pos;
    this->_type = type;
    this->_animsCount = animsCount;
    this->_animFrameCounter = animFrameCounter;
    this->_model = LoadModel("assets/monster/ia.obj");
    this->_texture = LoadTexture("assets/monster/textures/ia.png");
    this->_anims = LoadModelAnimations("assets/monster/animations/iaRun.iqm", &this->_animsCount);
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
}

void character::animation()
{
    UpdateModelAnimation(this->_model, this->_anims[0], this->_animFrameCounter);
    this->_animFrameCounter++;
    if (this->_animFrameCounter >= this->_anims[0].frameCount)
        this->_animFrameCounter = 0;
}

void character::draw()
{
    drawRayModel(this->_model, this->_position, 0.01f);
}

void character::handleInput()
{
    if (IsKeyDown(KEY_SPACE))
        this->animation();
}

void character::stop()
{
    UnloadModel(this->_model);
}

void character::run()
{
    this->handleInput();
    this->draw();
}
