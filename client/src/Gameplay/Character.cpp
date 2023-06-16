/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#include "encapsulation/Raylibcpp.hpp"
#include "src/Gameplay/Character.hpp"

#include <stdio.h>

Character::Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos, std::size_t level, std::size_t orientation, std::string name, std::size_t id, std::map<std::size_t, Texture2D> textures) : _position(pos), _animsCount(animsCount), _animFrameCounter(animFrameCounter), _currentlyAnimation(NONE), _level(level), _teamname(name)
{
    try {
        this->_id = id;
        this->_levelTmp = level;
        this->_inventory = std::make_shared<Inventory>();
        this->_model = this->_rayModel.loadModel("client/assets/monster/animations/monsterWalking.iqm");
        this->_textures = textures;
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterSpawn.iqm", &this->_animsCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterDying.iqm", &this->_animsCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterWalking.iqm", &this->_animsCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterRightTurn.iqm", &this->_animsCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterLeftTurn.iqm", &this->_animsCount));
        this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_textures[this->_level];
        if (orientation == 1)
            this->_currentDirection = NORTH;
        if (orientation == 2)
            this->_currentDirection = EAST;
        if (orientation == 3)
            this->_currentDirection = SOUTH;
        if (orientation == 4)
            this->_currentDirection = WEST;
        this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, _currentDirection * DEG2RAD});
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        exit (84);
    }
}

std::map<std::size_t, Texture2D> Character::getTextures() const
{
    return this->_textures;
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

void Character::checkLevel()
{
    if (this->_levelTmp != this->_level) {
        this->_levelTmp = this->_level;
        this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_textures[this->_level];
    }
}

void Character::run()
{
    this->checkLevel();
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

void Character::setPos(float x, float z, int orientation)
{
    if (this->_position.x != x || this->_position.z != z) {
        this->_position.x = x;
        this->_position.z = z;
        this->setCurrentlyAnimation(SPAWN);
    }
    this->_currentDirection = (orientation == 1) ? NORTH : (orientation == 2) ? EAST : (orientation == 3) ? SOUTH : WEST;
    this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, (float)_currentDirection * DEG2RAD});
}

size_t Character::getLevel() const
{
    return this->_level;
}

void Character::setLevel(size_t level)
{
    this->_level = level;
}

std::shared_ptr<Inventory> &Character::getInventory()
{
    return this->_inventory;
}

Directions Character::getDirection() const
{
    return this->_currentDirection;
}

void Character::setDirection(Directions direction)
{
    this->_currentDirection = direction;
}

std::string Character::getTeamName() const
{
    return this->_teamname;
}

std::size_t Character::getId() const
{
    return this->_id;
}

void Character::setBroadMessage(std::string message)
{
    this->_broadmessage = message;
}

std::string Character::getBroadMessage() const
{
    return this->_broadmessage;
}