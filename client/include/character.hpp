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
    #include "graphical.hpp"

class character : public graphical {
    public:
        character();
        ~character();
        void init(float x, float y, float z);
        void run();
        void stop();
        void draw();
        void handleInput();
    protected:
        Model model;
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
