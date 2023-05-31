/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** model
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::RayModel::drawRayModel(Model mod, Vector3 pos, float scale)
{
    DrawModel(mod, pos, scale, WHITE);
}

ModelAnimation *Raylibcpp::RayModel::loadModelAnimations(const char *fileName, unsigned int *animCount)
{
    return LoadModelAnimations(fileName, animCount);
}
