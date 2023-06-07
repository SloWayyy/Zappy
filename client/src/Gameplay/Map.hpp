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
    #include <unordered_map>
    #include "encapsulation/Raylibcpp.hpp"

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
        void fillMineralPositionArray();
        void drawMineral(modelType type);
        void setHeight(std::size_t height);
        void setWidth(std::size_t width);
        void openMap(std::string path);
        std::size_t getheight() const;
        std::size_t getwidth() const;
        std::vector<std::string> getMap() const {return map;};
        modelType getmodelBanana() const {return BANANA;};
        Vector3 getcubePosition() const;
        void setcubePosition(Vector3 position);
        void draw(Vector3 _position);
        void run();
    private:
        Model _model;
        Texture2D _texture;
        std::vector<std::string> map;
        mapSize _mapSize;
        Vector3 _cubePosition;
        std::unordered_map<modelType, std::pair<Model, Texture2D>> _modelMap;
        std::vector<Vector3> _MineralPositionArray;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayCube _rayCube;
};

#endif /* !MAP_HPP_ */