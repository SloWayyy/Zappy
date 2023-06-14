/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Map.cpp
*/

#include <fstream>
#include "src/Gameplay/Map.hpp"

Map::Map(std::size_t height, std::size_t width) : _mapSize{ height, width }, _cubePosition{ 0.0f, 0.0f, 0.0f }
{
    this->_level = this->_rayModel.loadTexture("assets/map/levelIcone.png");
    this->_team = this->_rayModel.loadTexture("assets/map/teamIcone.png");
    this->_model = this->_rayModel.loadModel("assets/map/floor.iqm");
    this->_texture = this->_rayModel.loadTexture("assets/map/floorTexture3.png");
    this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
    this->_modelPlatform = this->_rayModel.loadModel("assets/map/platform.iqm");
    this->_texturePlatform = this->_rayModel.loadTexture("assets/map/platformTexture.png");
    this->_modelPlatform.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texturePlatform;
    this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
    this->_modelPlatform.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
    this->_modelMap.insert({this->BANANA, std::make_pair(this->_rayModel.loadModel("assets/food/banana/banana.obj"), this->_rayModel.loadTexture("assets/food/banana/banana.png"))});
    // this->_modelMap.insert({this->APPLE, std::make_pair(this->_rayModel.loadModel("assets/food/apple/apple.obj"), this->_rayModel.loadTexture("assets/food/apple/apple.png"))});
    this->_rayModel.setMaterialTexture(&this->_modelMap[this->BANANA].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->BANANA].second);
    // this->_rayModel.setMaterialTexture(&this->_modelMap[this->APPLE].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->APPLE].second);
}

void Map::drawMineral(modelType type, Vector3 position)
{
    this->_rayModel.drawModel(this->_modelMap[type].first, position, 0.5f, WHITE);
}

void Map::draw(Model model, Vector3 _position, float scale)
{
    this->_rayModel.drawModel(model, _position, scale, WHITE);
}

void Map::run()
{
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
