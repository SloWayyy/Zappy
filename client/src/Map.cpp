/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Map.cpp
*/

#include "Map.hpp"

Map::Map(int height, float width)
{
    this->height = height;
    this->width = width;
    this->x = 0.0f;
    this->y = 0.0f;
    this->cubePosition = { x, 0.0f, y };
}

Map::~Map()
{
}

void Map::draw()
{
    x = 0.0f;
    y = 0.0f;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector3 cubePosition = { x, 0.0f, y };
            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
            DrawGrid(10, 1.0f);
            x += 2.0f;
        }
        x = 0.0f;
        y += 2.0f;
    }
    DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines( 10, 10, 320, 133, BLUE);
}

int Map::getheight()
{
    return height;
}

int Map::getwidth()
{
    return width;
}

Vector3 Map::getcubePosition()
{
    return cubePosition;
}
