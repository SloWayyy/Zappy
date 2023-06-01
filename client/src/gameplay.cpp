/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#include "gameplay.hpp"

Gameplay::Gameplay()
{
    this->_map = Map(10, 10);
    this->_characters = std::vector<character>();
}

void Gameplay::initPlayer(void)
{
    character player(0, 0, {0, 1.1, 2});

    _characters.push_back(player);
}

void Gameplay::runPlayers(void)
{
    for (auto &character : this->_characters) {
        character.run();
    }
}

void Gameplay::run(void)
{
    this->_map.run();
    this->runPlayers();
}
