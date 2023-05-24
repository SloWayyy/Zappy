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

class Map {
    public:
        Map(int height, float width);
        ~Map();
        void draw();
        int getheight();
        int getwidth();
        Vector3 getcubePosition();
    private:
        int height;
        float width;
        Vector3 cubePosition;
        float x;
        float y;
};

#endif /* !MAP_HPP_ */