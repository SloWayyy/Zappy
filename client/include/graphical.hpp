/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** graphical
*/

#ifndef GRAPHICAL_HPP_
    #define GRAPHICAL_HPP_

    #include <string>
    #include <iostream>
    #include <vector>
    #include "raylib.h"
    #include "character.hpp"
    #include "Map.hpp"

static constexpr int WIDTH = 1920;
static constexpr int HEIGHT = 1080;

class graphical {
    public:
        graphical();
        ~graphical() = default;
        void init();
        void run();
        void stop();
        void draw();
        void update();
        void setCamera();
        void setCameraPosition(float x, float y, float z);
        Camera getCamera() const { return camera; };
        void handleInput();
        void draw_all_players();
        std::vector<character> players;
    protected:
        Camera camera;
        Vector3 cubePosition;
        Map map;
        float pos_x;
        float pos_y;
    private:
};

#endif /* !GRAPHICAL_HPP_ */
