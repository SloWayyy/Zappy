/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** draw
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::Draw::drawCube(Vector3 pos, float width, float height, float lenght, Color color)
{
    DrawCube(pos, width, height, lenght, color);
}

void Raylibcpp::Draw::drawCubeWires(Vector3 pos, float width, float height, float lenght, Color color)
{
    DrawCubeWires(pos, width, height, lenght, color);
}

void Raylibcpp::Draw::drawTexture(Texture2D texture, int posX, int posY, Color color)
{
    DrawTexture(texture, posX, posY, color);
}
