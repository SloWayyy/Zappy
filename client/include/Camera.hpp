/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include <string>
    #include <iostream>
    #include "raylib.h"

namespace LIB {
    class Camera_Gui {
        public:
            Camera_Gui();
            ~Camera_Gui();
            void setPosition(float x, float y, float z);
            void setTarget(float x, float y, float z);
            void setProjection(int projection);
            void setUp(float x, float y, float z);
            void setFovy(float fovy);
            Camera getCamera();
            float getFovy();
            Vector3 getPosition();
            Vector3 getTarget();
            Vector3 getUp();
            int getProjection();
            void updateCam(int mode);
        private:
            Camera camera;

    };
}

#endif /* !CAMERA_HPP_ */