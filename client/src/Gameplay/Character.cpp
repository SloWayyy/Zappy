/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#include "encapsulation/Raylibcpp.hpp"
#include "src/Gameplay/Character.hpp"

#include <stdio.h>

Character::Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos) : _position(pos), _animsCount(animsCount), _animFrameCounter(animFrameCounter), _currentlyAnimation(NONE)
{
    this->_model = this->_rayModel.loadModel("assets/monster/animations/monsterWalking.iqm");
    this->_texture = this->_rayModel.loadTexture("assets/monster/textures/monsterTexture.png");
    this->_animations.push_back(this->_rayModel.loadModelAnimations("assets/monster/animations/monsterSpawn.iqm", &this->_animsCount));
    this->_animations.push_back(this->_rayModel.loadModelAnimations("assets/monster/animations/monsterDying.iqm", &this->_animsCount));
    this->_animations.push_back(this->_rayModel.loadModelAnimations("assets/monster/animations/monsterWalking.iqm", &this->_animsCount));
    this->_animations.push_back(this->_rayModel.loadModelAnimations("assets/monster/animations/monsterRightTurn.iqm", &this->_animsCount));
    this->_animations.push_back(this->_rayModel.loadModelAnimations("assets/monster/animations/monsterLeftTurn.iqm", &this->_animsCount));
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
    this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, RIGHT_DIR});
    this->_currentDirection = RIGHT_DIR;
}

void Character::chooseAnimation(Animations anim)
{
    if (this->_animFrameCounter < this->_animations[anim][0].frameCount) {
        this->_rayModel.updateModelAnimation(this->_model, this->_animations[anim][0], this->_animFrameCounter);
        this->_animFrameCounter++;
    }
    if (this->_animFrameCounter >= this->_animations[anim][0].frameCount) {
        this->_animFrameCounter = 0;
        this->_currentlyAnimation = NONE;
    }
}

void Character::draw()
{
    this->_rayModel.drawModel(this->_model, this->_position, 0.05f, WHITE);
}

void Character::run()
{
    this->draw();
    this->handleEvent();
}

Vector3 Character::getPosition() const
{
    return this->_position;
}

Model Character::getModel() const
{
    return this->_model;
}

int Character::getAnimFrameCounter() const
{
    return this->_animFrameCounter;
}

ModelAnimation *Character::getAnimation(Animations anim) const
{
    return this->_animations[anim];
}

void Character::setAnimFrameCounter(int animFrameCounter)
{
    this->_animFrameCounter = animFrameCounter;
}

Animations Character::getCurrentlyAnimation() const
{
    return this->_currentlyAnimation;
}

void Character::setCurrentlyAnimation(Animations currentlyAnimation)
{
    this->_currentlyAnimation = currentlyAnimation;
}

void Character::handleEvent()
{
    if (this->_currentlyAnimation == SPAWN)
        this->chooseAnimation(SPAWN);
    if (this->_currentlyAnimation == DYING)
        this->chooseAnimation(DYING);
    if (this->_currentlyAnimation == WALKING)
        this->chooseAnimation(WALKING);
    if (this->_currentlyAnimation == RIGHT_TURN)
        this->chooseAnimation(RIGHT_TURN);
    if (this->_currentlyAnimation == LEFT_TURN)
        this->chooseAnimation(LEFT_TURN);
}

void Character::setPos(int x, int z, int orientation)
{
    if (this->_position.x != x || this->_position.z != z) {
        this->_position.x = (this->_position.x < x) ? x + 3 : (this->_position.x > x) ? x - 3 : this->_position.x;
        this->_position.z = (this->_position.z < z) ? z + 3 : (this->_position.z > z) ? z - 3 : this->_position.z;
        this->setCurrentlyAnimation(SPAWN);
    }
    this->_currentDirection = (Directions)orientation;
    this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, (float)_currentDirection * DEG2RAD});
}
