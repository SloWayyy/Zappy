/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

LIB::Camera_Gui::Camera_Gui()
{
    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 10.0f, 2.0f, 10.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
}

LIB::Camera_Gui::~Camera_Gui()
{
}

void LIB::Camera_Gui::setPosition(float x, float y, float z)
{
    camera.position = (Vector3){ x, y, z };
}

Vector3 LIB::Camera_Gui::getPosition()
{
    return camera.position;
}

void LIB::Camera_Gui::setTarget(float x, float y, float z)
{
    camera.target = (Vector3){ x, y, z };
}

Vector3 LIB::Camera_Gui::getTarget()
{
    return camera.target;
}

void LIB::Camera_Gui::setProjection(int projection)
{
    camera.projection = projection;
}

int LIB::Camera_Gui::getProjection()
{
    return camera.projection;
}

void LIB::Camera_Gui::setUp(float x, float y, float z)
{
    camera.up = (Vector3){ x, y, z };
}

Vector3 LIB::Camera_Gui::getUp()
{
    return camera.up;
}

void LIB::Camera_Gui::setFovy(float fovy)
{
    camera.fovy = fovy;
}

float LIB::Camera_Gui::getFovy()
{
    return camera.fovy;
}

void LIB::Camera_Gui::updateCam(int mode)
{
    UpdateCamera(&camera, mode);
}

