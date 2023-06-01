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
    this->_mapSize = { height, width };
    this->_cubePosition = { 0.0f, 0.0f, 0.0f };
    this->openMap("../map.txt");
    this->_modelMap.insert({this->BANANA, std::make_pair(LoadModel("assets/food/banana/banana.obj"), LoadTexture("assets/food/banana/banana.png"))});
    this->_modelMap.insert({this->APPLE, std::make_pair(LoadModel("assets/food/apple/apple.obj"), LoadTexture("assets/food/apple/apple.png"))});
    SetMaterialTexture(&this->_modelMap[this->BANANA].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->BANANA].second);
    SetMaterialTexture(&this->_modelMap[this->APPLE].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->APPLE].second);
    this->fillMineralPositionArray();
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

void Map::drawMineral(modelType type)
{
    for (auto &i : this->_MineralPositionArray) {
        DrawModel(this->_modelMap[type].first, i, 1.0f, WHITE);
    }
}

void Map::fillMineralPositionArray()
{
    float _x = 0.0f;
    float _y = 0.0f;

    for (std::size_t y = 0; y < this->_mapSize.height; y++) {
        for (std::size_t x = 0; x < this->_mapSize.width; x++) {
            if (map[y][x] == 'O')
                this->_MineralPositionArray.push_back({ _x, 1.0f, _y });
            _x += 2.0f;
        }
        _x = 0.0f;
        _y += 2.0f;
    }
}

void Map::draw()
{
    float _x = 0.0f;
    float _y = 0.0f;

    for (std::size_t y = 0; y < this->_mapSize.height; y++) {
        for (std::size_t x = 0; x < this->_mapSize.width; x++) {
            this->_cubePosition = { _x, 0.0f, _y };
            DrawCube(this->_cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
            DrawCubeWires(this->_cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
        _x += 2.0f;
        }
        _x = 0.0f;
        _y += 2.0f;
    }
    this->drawMineral(this->BANANA);
}

void Map::run()
{
    this->draw();
}

void Map::setHeight(std::size_t height)
{
    this->_mapSize.height = height;
}

void Map::setWidth(std::size_t width)
{
    this->_mapSize.width = width;
}

std::size_t Map::getheight() const
{
    return this->_mapSize.height;
}

std::size_t Map::getwidth() const
{
    return this->_mapSize.width;
}

Vector3 Map::getcubePosition() const
{
    return this->_cubePosition;
}

void Map::setcubePosition(Vector3 position)
{
    this->_cubePosition = position;
}
