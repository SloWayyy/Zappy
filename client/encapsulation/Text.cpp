/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** text
*/

#include "encapsulation/Raylibcpp.hpp"

Raylibcpp::RayText::RayText(std::string string, int posX, int posY, int fontSize, Color color) : _string(string), _posX(posX), _posY(posY), _fontSize(fontSize), _color(color)
{
}

void Raylibcpp::RayText::drawText(std::string string, int posX, int posY, int fontSize, Color color)
{
    DrawText(const_cast<char*> (string.c_str()), posX, posY, fontSize, color);
}

void Raylibcpp::RayText::setString(const std::string &string)
{
    _string = string;
}

std::string Raylibcpp::RayText::getString() const
{
    return _string;
}