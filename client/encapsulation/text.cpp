/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** text
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::Text::drawText(std::string string, int posX, int posY, int fontSize, Color color)
{
    DrawText(string.c_str(), posX, posY, fontSize, color);
}

void Raylibcpp::Text::drawFontText(std::string text, int x, int y, int size, Color color)
{
    Font font = GetFontDefault();
    font.baseSize = size;
    DrawTextEx(font, text.c_str(), {static_cast<float>(x), static_cast<float>(y)}, static_cast<float>(size), 1, color);
}
