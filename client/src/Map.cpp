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
    this->cubePosition = { 0, 0.0f, 0 };
}

Map::~Map()
{
}

void Map::draw()
{
    float _x = 0.0f;
    float _y = 0.0f;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cubePosition = { _x, 0.0f, _y };
            drawCube(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
            drawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
            DrawGrid(10, 1.0f);
            _x += 2.0f;
        }
        _x = 0.0f;
        _y += 2.0f;
    }
}

void Map::run()
{
    this->draw();
}
