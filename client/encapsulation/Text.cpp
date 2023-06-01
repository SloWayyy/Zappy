/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** text
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::RayText::drawText(std::string string, int posX, int posY, int fontSize, Color color)
{
    DrawText(const_cast<char*> (string.c_str()), posX, posY, fontSize, color);
}
