/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#include "character.hpp"
#include "IGraphical.hpp"

character::character()
{
    animsCount = 0;
    animFrameCounter = 0;
    animId = 0;
    drawMesh = 1;
    drawSkeleton = 2;
    animPlaying = false;
}

void character::init(float x, float y, float z)
{
    position = { x, y, z };
    // char modelFileName[128] = "cesium_man.m3d";
    // model = LoadModel(modelFileName);
    // anims = LoadModelAnimations(modelFileName, &animsCount);
}

void character::draw()
{
    if (drawMesh)
        DrawModel(model, position, 1.0f, WHITE);
    if (drawSkeleton) {
        for (int i = 0; i < model.boneCount - 1; i++) {
            if (!animPlaying || !animsCount) {
                DrawCube(model.bindPose[i].translation, 0.04f, 0.04f, 0.04f, RED);
                if (model.bones[i].parent >= 0) {
                    DrawLine3D(model.bindPose[i].translation,
                        model.bindPose[model.bones[i].parent].translation, RED);
                }
            } else {
                DrawCube(anims[animId].framePoses[animFrameCounter][i].translation, 0.05f, 0.05f, 0.05f, RED);
                if (anims[animId].bones[i].parent >= 0) {
                    DrawLine3D(anims[animId].framePoses[animFrameCounter][i].translation,
                        anims[animId].framePoses[animFrameCounter][anims[animId].bones[i].parent].translation, RED);
                }
            }
        }
    }
}

void character::handleInput()
{
    if (animsCount) {
        if (IsKeyDown(KEY_SPACE) || IsKeyPressed(KEY_N)) {
            animFrameCounter++;
            if (animFrameCounter >= anims[animId].frameCount)
                animFrameCounter = 0;
            UpdateModelAnimation(model, anims[animId], animFrameCounter);
            animPlaying = true;
        }
        if (IsKeyPressed(KEY_A)) {
            animFrameCounter = 0;
            animId++;
            if (animId >= animsCount)
                animId = 0;
            UpdateModelAnimation(model, anims[animId], 0);
            animPlaying = true;
        }
    }
    if (IsKeyPressed(KEY_S))
        drawSkeleton ^= 1;
    if (IsKeyPressed(KEY_M))
        drawMesh ^= 1;
}

void character::stop()
{
    UnloadModelAnimations(anims, animsCount);
    UnloadModel(model);
}

void character::setposition(Vector3 position)
{
    this->position = position;
}

Vector3 character::getposition()
{
    return position;
}

void character::prepareCharacter(float x, float z, Raylibcpp::RayModel::modelType modl)
{
    Vector3 cubePosition = {x, 0.6, z};

    switch(modl) {
        case (Raylibcpp::RayModel::modelType::PING):
            drawRayModel(modl, cubePosition, 0.02f);
            break;
    }
}

void character::displayCharacter()
{
    this->draw();
    this->handleInput();
}

void character::run()
{
    // this->draw();
    // this->handleInput();
    this->prepareCharacter(position.x, position.z, Raylibcpp::RayModel::modelType::PING);
}
