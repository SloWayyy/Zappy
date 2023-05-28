/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Map.cpp
*/

#include <fstream>
#include <array>
#include "Map.hpp"

Map::Map(std::size_t height, std::size_t width)
{
    this->_height = height;
    this->_width = width;
    this->_cubePosition = { 0.0f, 0.0f, 0.0f };
    this->_currentMineral = 0;
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
    for (auto &i : model) {
        this->modelArray.push_back(modelLoad(LoadModel(i.second.first.c_str()), LoadTexture(i.second.second.c_str())));
        SetMaterialTexture(&this->modelArray.back()._model.materials[0], MATERIAL_MAP_DIFFUSE, this->modelArray.back()._texture);
    }
}

void Map::drawMineral()
{
    for (auto &i : this->_MineralPositionArray) {
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

    for (std::size_t y = 0; y < this->_height; y++) {
        for (std::size_t x = 0; x < this->_width; x++) {
            if (map[y][x] == 'X') {
                this->_cubePosition = { _x, 0.0f, _y };
                drawCube(this->_cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
                drawCubeWires(this->_cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
            }
            if (map[y][x] == 'O') {
                this->_cubePosition = { _x, 0.0f, _y };
                drawCube(this->_cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
                drawCubeWires(this->_cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
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
