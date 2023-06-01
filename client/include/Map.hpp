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

typedef struct mapSize_s {
    std::size_t height;
    std::size_t width;
} mapSize_t;

class Map {
    enum modelType {
        BANANA,
        APPLE,
    };
    public:
        Map() = default;
        Map(std::size_t height , std::size_t width);
        ~Map() = default;
        void draw();
        void fillMineralPositionArray();
        void drawMineral(modelType type);
        void setHeight(std::size_t height);
        void setWidth(std::size_t width);
        void openMap(std::string path);
        std::size_t getheight() const;
        std::size_t getwidth() const;
        Vector3 getcubePosition() const;
        void setcubePosition(Vector3 position);
        void run();
    private:
        Model _model;
        Texture2D _texture;
        Vector3 _cubePosition;
        std::vector<std::string> map;
        mapSize_t _mapSize;
        std::unordered_map<modelType, std::pair<Model, Texture2D>> _modelMap;
        std::vector<Vector3> _MineralPositionArray;

};

#endif /* !MAP_HPP_ */