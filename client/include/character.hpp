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
        character();
        ~character() = default;
        void init(float x, float y, float z);
        void setposition(Vector3 position);
        Vector3 getposition();
        void run();
        void stop();
        void draw();
        void handleInput();
        void prepareCharacter(float x, float z, Raylibcpp::RayModel::modelType modl);
        void displayCharacter();
    protected:
        Model model;
        std::vector<pos_t> skinPos;
        ModelAnimation *anims;
        Vector3 position;
        unsigned int animsCount;
        int animFrameCounter;
        int animId;
        bool drawMesh;
        bool drawSkeleton;
        bool animPlaying;
    private:
};

#endif /* !CHARACTER_HPP_ */
