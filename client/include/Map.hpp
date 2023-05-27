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
    #include "raylib.h"
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
        Map(int height, float width);
        ~Map();
        void draw();
        void initMineral();
        void drawMineral();
        void openMap(std::string path);
        int getheight() const {return height;};
        int getwidth() const {return width;};
        Vector3 getcubePosition() const {return cubePosition;};
        void setcubePosition(Vector3 position) {cubePosition = position;};
        void run();
    private:
        int height;
        float width;
        std::size_t _currentMineral;
        std::vector<modelLoad> modelArray;
        Model _model;
        std::vector<Vector3> _MineralPositionArray;
        Texture2D _texture;
        Vector3 cubePosition;
        std::vector<std::string> map;
};

#endif /* !MAP_HPP_ */