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
    try {
        this->_level = this->_rayModel.loadTexture("client/assets/map/levelIcone.png");
        this->_team = this->_rayModel.loadTexture("client/assets/map/teamIcone.png");
        this->_model = this->_rayModel.loadModel("client/assets/map/floor.iqm");
        this->_texture = this->_rayModel.loadTexture("client/assets/map/floorTexture3.png");
        this->_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texture;
        this->_modelPlatform = this->_rayModel.loadModel("client/assets/map/platform.iqm");
        this->_texturePlatform = this->_rayModel.loadTexture("client/assets/map/platformTexture.png");
        this->_modelPlatform.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_texturePlatform;
        this->_model.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelPlatform.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelSkybox = this->_rayModel.loadModel("client/assets/map/skybox.iqm");
        this->_textureSkyboxMorning = this->_rayModel.loadTexture("client/assets/map/skyboxTexture2.png");
        this->_modelSkybox.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_textureSkyboxMorning;
        this->_textureSkyboxNight = this->_rayModel.loadTexture("client/assets/map/skyboxTexture.png");
        this->_modelSkybox.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelMap.insert({this->FOOD, std::make_pair(this->_rayModel.loadModel("client/assets/food/food.iqm"), this->_rayModel.loadTexture("client/assets/food/foodTexture.png"))});
        this->_modelMap.insert({this->LINEMATE, std::make_pair(this->_rayModel.loadModel("client/assets/Mineral/crystal.iqm"), this->_rayModel.loadTexture("client/assets/Mineral/Linemate.png"))});
        this->_modelMap.insert({this->DERAUMERE, std::make_pair(this->_rayModel.loadModel("client/assets/Mineral/crystal.iqm"), this->_rayModel.loadTexture("client/assets/Mineral/Deraumere.png"))});
        this->_modelMap.insert({this->SIBUR, std::make_pair(this->_rayModel.loadModel("client/assets/Mineral/crystal.iqm"), this->_rayModel.loadTexture("client/assets/Mineral/Sibur.png"))});
        this->_modelMap.insert({this->MENDIANE, std::make_pair(this->_rayModel.loadModel("client/assets/Mineral/crystal.iqm"), this->_rayModel.loadTexture("client/assets/Mineral/Mendiane.png"))});
        this->_modelMap.insert({this->PHIRAS, std::make_pair(this->_rayModel.loadModel("client/assets/Mineral/crystal.iqm"), this->_rayModel.loadTexture("client/assets/Mineral/Phiras.png"))});
        this->_modelMap.insert({this->THYSTAME, std::make_pair(this->_rayModel.loadModel("client/assets/Mineral/crystal.iqm"), this->_rayModel.loadTexture("client/assets/Mineral/Thystame.png"))});
        this->_modelMap[this->LINEMATE].first.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelMap[this->DERAUMERE].first.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelMap[this->SIBUR].first.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelMap[this->MENDIANE].first.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelMap[this->PHIRAS].first.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_modelMap[this->THYSTAME].first.transform = this->_rayModel.matrixRotateXYZ({-90 * DEG2RAD, 0, 0});
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->FOOD].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->FOOD].second);
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->LINEMATE].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->LINEMATE].second);
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->DERAUMERE].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->DERAUMERE].second);
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->SIBUR].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->SIBUR].second);
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->MENDIANE].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->MENDIANE].second);
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->PHIRAS].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->PHIRAS].second);
        this->_rayModel.setMaterialTexture(&this->_modelMap[this->THYSTAME].first.materials[0], MATERIAL_MAP_DIFFUSE, this->_modelMap[this->THYSTAME].second);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        exit (84);
    }
}

Map::~Map()
{
    this->_rayModel.unloadTexture(this->_level);
    this->_rayModel.unloadTexture(this->_team);
    this->_rayModel.unloadModel(this->_model);
    this->_rayModel.unloadTexture(this->_texture);
    this->_rayModel.unloadModel(this->_modelPlatform);
    this->_rayModel.unloadTexture(this->_texturePlatform);
    this->_rayModel.unloadModel(this->_modelSkybox);
    this->_rayModel.unloadTexture(this->_textureSkyboxMorning);
    this->_rayModel.unloadTexture(this->_textureSkyboxNight);
    this->_rayModel.unloadModel(this->_modelMap[this->FOOD].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->FOOD].second);
    this->_rayModel.unloadModel(this->_modelMap[this->LINEMATE].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->LINEMATE].second);
    this->_rayModel.unloadModel(this->_modelMap[this->DERAUMERE].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->DERAUMERE].second);
    this->_rayModel.unloadModel(this->_modelMap[this->SIBUR].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->SIBUR].second);
    this->_rayModel.unloadModel(this->_modelMap[this->MENDIANE].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->MENDIANE].second);
    this->_rayModel.unloadModel(this->_modelMap[this->PHIRAS].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->PHIRAS].second);
    this->_rayModel.unloadModel(this->_modelMap[this->THYSTAME].first);
    this->_rayModel.unloadTexture(this->_modelMap[this->THYSTAME].second);
}

void Map::drawMineral(modelType type, Vector3 position, float scale)
{
    this->_rayModel.drawModel(this->_modelMap[type].first, position, scale, WHITE);
}

void Map::draw(Model model, Vector3 _position, float scale)
{
    this->_rayModel.drawModel(model, _position, scale, WHITE);
}

void Map::drawColor(Model model, Vector3 _position, float scale, Color color)
{
    this->_rayModel.drawModel(model, _position, scale, color);
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

std::vector<std::string> &Map::getMap()
{
    return this->map;
}

Model Map::getmodel() const
{
    return this->_model;
}

Model Map::getmodelPlatform() const
{
    return this->_modelPlatform;
}

Model Map::getmodelSkybox() const
{
    return this->_modelSkybox;
}

Texture2D Map::getLevel () const
{
    return this->_level;
}

Texture2D Map::getTeam () const
{
    return this->_team;
}

std::map<std::pair<std::size_t, std::size_t>, std::array<int, 7>> &Map::getMapInventory()
{
    return this->_mapInventory;
}

void Map::setNight()
{
    this->_modelSkybox.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_textureSkyboxNight;
}

void Map::setMorning()
{
    this->_modelSkybox.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_textureSkyboxMorning;
}
