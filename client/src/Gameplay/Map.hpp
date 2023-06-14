/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Map.hpp
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <string>
    #include <iostream>
    #include <vector>
    #include <map>
    #include <unordered_map>
    #include "encapsulation/Raylibcpp.hpp"
    #include <array>

struct mapSize {
    std::size_t height;
    std::size_t width;
};

class Map {
    enum modelType {
        BANANA,
        APPLE,
    };
    public:
        Map() = default;
        Map(std::size_t height , std::size_t width);
        ~Map() = default;
        void drawMineral(modelType type, Vector3 position);
        void setHeight(std::size_t height);
        void setWidth(std::size_t width);
        std::size_t getheight() const;
        std::size_t getwidth() const;
        std::vector<std::string> &getMap() {return map;};
        modelType getmodelBanana() const {return BANANA;};
        Vector3 getcubePosition() const;
        void setcubePosition(Vector3 position);
        Model getmodel() const {return _model;};
        Model getmodelPlatform() const {return _modelPlatform;};
        void draw(Model model, Vector3 _position, float scale);
        Texture2D getLevel() const {return _level;};
        Texture2D getTeam() const {return _team;};
        std::map<std::pair<std::size_t, std::size_t>, std::array<int, 7>> &getMapInventory() {return _mapInventory;};
        void run();
    private:
        Model _model;
        Texture2D _texture;
        Model _modelPlatform;
        Texture2D _texturePlatform;
        std::vector<std::string> map;
        mapSize _mapSize;
        Vector3 _cubePosition;
        std::unordered_map<modelType, std::pair<Model, Texture2D>> _modelMap;
        std::vector<Vector3> _MineralPositionArray;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayCube _rayCube;
        Texture2D _level;
        Texture2D _team;
        std::map<std::pair<std::size_t, std::size_t>, std::array<int, 7>> _mapInventory;
};

#endif /* !MAP_HPP_ */