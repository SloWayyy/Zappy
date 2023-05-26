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
            struct modelLoad {
                modelLoad(Model model, modelType type, unsigned int animsCount, int animFrameCounter, Texture2D texure) : _model(model), _type(type),
                                                                                                                          _animFrameCounter(animFrameCounter), _animsCount(animsCount), _texture(texure) {}
                Model _model;
                modelType _type;
                unsigned int _animsCount;
                int _animFrameCounter;
                Texture2D _texture;
            };
            RayModel();
            modelLoad &getModelLoad(modelType type);
            Texture2D getTexture(modelType type);
            void drawRayModel(Raylibcpp::RayModel::modelType type, Vector3 pos, float scale);
            ~RayModel();
        private:
            std::vector<modelLoad> _modelArray;
    };
    class Draw : public Raylibcpp::RayModel {
        public:
        Draw() = default;
        ~Draw() = default;
        void drawCube(Vector3 pos, float widht, float height, float lenght, Color color);
        void drawCubeWires(Vector3 pos, float widht, float height, float lenght, Color color);
    private:
    protected:
    };
    // class Environment : public Raylibcpp::Draw {
    //     public:
    //         enum textureStyle {
    //             FLOOR = 1,
    //         };
    //         struct textureLoad {
    //             textureLoad(Texture2D text, textureStyle style) : _texture(text), _style(style) {}
    //             Texture2D _texture;
    //             textureStyle _style;
    //         };
    //         Environment();
    //         ~Environment();
    //         void drawTextureCube(float x, float y, float z, Vector3 dim, textureStyle style);
    //         void drawSphere(Vector3 pos, float radius, Color color);
    //         void drawBackground(textureStyle style);
    //         Texture2D getTexture(textureStyle style);
    //     private:
    //         std::vector<textureLoad> _textureArray;
    //     protected:
    // };
}

#endif /* !RAYLIBCPP_HPP_ */
