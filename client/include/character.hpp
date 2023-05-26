/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#ifndef CHARACTER_HPP_
    #define CHARACTER_HPP_

    #include <string>
    #include <iostream>
    #include "raylib.h"
    #include "encapsulation/Raylibcpp.hpp"

typedef struct pos_s
{
    float x;
    float y;
} pos_t;

class character : public Raylibcpp::RayModel {
    public:
        character(Raylibcpp::RayModel::modelType type, unsigned int animsCount, int animFrameCounter, Vector3 pos);
        character() = default;
        ~character() = default;
        void run();
        void stop();
        void draw();
        void handleInput();
    protected:
        Model _model;
        modelType _type;
        unsigned int _animsCount;
        int _animFrameCounter;
        Texture2D _texture;
        Vector3 _position;
    private:
};

#endif /* !CHARACTER_HPP_ */
