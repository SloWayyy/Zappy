/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Raylibcpp
*/

#ifndef RAYLIBCPP_HPP_
    #define RAYLIBCPP_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <raylib.h>

namespace Raylibcpp {
    class RayModel {
        public:
            enum modelType {
                PING
            };
            RayModel() = default;
            Texture2D getTexture(modelType type);
            void drawRayModel(Model mod, Vector3 pos, float scale);
            ~RayModel() = default;
        private:
    };
    class Draw : public Raylibcpp::RayModel {
        public:
        Draw() = default;
        ~Draw() = default;
        void drawCube(Vector3 pos, float widht, float height, float lenght, Color color);
        void drawCubeWires(Vector3 pos, float widht, float height, float lenght, Color color);
        void drawTexture(Texture2D texture, int posX, int posY, Color color);
    private:
    protected:
    };
}

#endif /* !RAYLIBCPP_HPP_ */
