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
    public:
        Map() = default;
        Map(int height, float width);
        ~Map();
        void draw();
        int getheight() const {return height;};
        int getwidth() const {return width;};
        Vector3 getcubePosition() const {return cubePosition;};
        void setcubePosition(Vector3 position) {cubePosition = position;};
        void run();
    private:
        int height;
        float width;
        Vector3 cubePosition;
};

#endif /* !MAP_HPP_ */