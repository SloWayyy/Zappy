/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Mouse
*/

#include "encapsulation/Raylibcpp.hpp"

bool Raylibcpp::RayMouse::isMouseButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

bool Raylibcpp::RayMouse::isMouseButtonReleased(int button)
{
    return IsMouseButtonReleased(button);
}

bool Raylibcpp::RayMouse::isMouseButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

bool Raylibcpp::RayMouse::checkCollisionRecs(Rectangle rec1, Rectangle rec2)
{
    return CheckCollisionRecs(rec1, rec2);
}

Vector2 Raylibcpp::RayMouse::getMousePosition(void)
{
    return GetMousePosition();
}

int Raylibcpp::RayMouse::getMouseX(void)
{
    return GetMouseX();
}

int Raylibcpp::RayMouse::getMouseY(void)
{
    return GetMouseY();
}
