/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Map.cpp
*/

#include <fstream>
#include "Map.hpp"

Map::Map(int height, float width)
{
    this->height = height;
    this->width = width;
    this->cubePosition = { 0.0f, 0.0f, 0.0f };
    this->_currentMineral = 0;
    // this->initMineral();
    this->openMap("../map.txt");
}

Map::~Map()
{
}

void Map::initMineral()
{
    std::array<std::pair<modelType, std::pair<std::string, std::string>>, 1> model = {
        {
            {this->BANANA, {"assets/food/banana/banana.obj", "assets/food/banana/banana.png"}},
            // {this->APPLE, {"assets/food/apple/Apple.obj", "assets/food/apple/Apple.png"}},
        }
    };
    for (const auto &i : model) {
        this->modelArray.push_back(modelLoad(LoadModel(i.second.first.c_str()), LoadTexture(i.second.second.c_str())));
        SetMaterialTexture(&this->modelArray.back()._model.materials[0], MATERIAL_MAP_DIFFUSE, this->modelArray.back()._texture);
    }
}

void Map::drawMineral()
{
    for (const auto &i : this->_MineralPositionArray) {
        drawRayModel(this->modelArray[0]._model, i, 1.0f);
    }
}

void Map::openMap(std::string path)
{
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: cannot open file" << std::endl;
        return;
    }
    while (std::getline(file, line))
        this->map.push_back(line);
    file.close();
}

void Map::draw()
{
    float _x = 0.0f;
    float _y = 0.0f;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == 'X') {
                cubePosition = { _x, 0.0f, _y };
                drawCube(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
                drawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
            }
            if (map[y][x] == 'O') {
                cubePosition = { _x, 0.0f, _y };
                drawCube(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
                drawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
                this->_MineralPositionArray.push_back({ _x, 1.0f, _y });
                drawMineral();
            }
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
