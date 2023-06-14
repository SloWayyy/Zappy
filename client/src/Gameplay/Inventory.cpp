/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Inventory.cpp
*/

#include "Inventory.hpp"

Inventory::Inventory() : _food(0), _linemate(0), _deraumere(0), _sibur(0), _mendiane(0), _phiras(0), _thystame(0)
{
}

void Inventory::setFood(std::size_t food)
{
    this->_food = food;
}

void Inventory::setLinemate(std::size_t linemate)
{
    this->_linemate = linemate;
}

void Inventory::setDeraumere(std::size_t deraumere)
{
    this->_deraumere = deraumere;
}

void Inventory::setSibur(std::size_t sibur)
{
    this->_sibur = sibur;
}

void Inventory::setMendiane(std::size_t mendiane)
{
    this->_mendiane = mendiane;
}

void Inventory::setPhiras(std::size_t phiras)
{
    this->_phiras = phiras;
}

void Inventory::setThystame(std::size_t thystame)
{
    this->_thystame = thystame;
}

std::size_t Inventory::getFood() const
{
    return this->_food;
}

std::size_t Inventory::getLinemate() const
{
    return this->_linemate;
}

std::size_t Inventory::getDeraumere() const
{
    return this->_deraumere;
}

std::size_t Inventory::getSibur() const
{
    return this->_sibur;
}

std::size_t Inventory::getMendiane() const
{
    return this->_mendiane;
}

std::size_t Inventory::getPhiras() const
{
    return this->_phiras;
}

std::size_t Inventory::getThystame() const
{
    return this->_thystame;
}
