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
    #include "encapsulation/Raylibcpp.hpp"

class Map : public Raylibcpp::Draw {
    enum modelType {
        BANANA,
        APPLE,
    };
    struct modelLoad {
        modelLoad(Model model, Texture2D texure) : _model(model), _texture(texure) {};
        Model _model;
        Texture2D _texture;
    };
    public:
        Map() = default;
        Map(std::size_t height, std::size_t width);
        ~Map();
        void draw();
        void initMineral();
        void drawMineral();
        void setHeight(std::size_t height) {this->_height = height;};
        void setWidth(std::size_t width) {this->_width = width;};
        void openMap(std::string path);
        std::size_t getheight() const {return this->_height;};
        std::size_t getwidth() const {return this->_width;};
        Vector3 getcubePosition() const {return this->_cubePosition;};
        void setcubePosition(Vector3 position) {this->_cubePosition = position;};
        void run();
    private:
        std::size_t _height;
        std::size_t _width;
        std::size_t _currentMineral;
        std::vector<modelLoad> modelArray;
        Model _model;
        std::vector<Vector3> _MineralPositionArray;
        Texture2D _texture;
        Vector3 _cubePosition;
        std::vector<std::string> map;
};

#endif /* !MAP_HPP_ */