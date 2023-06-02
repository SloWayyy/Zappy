/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** AScreen
*/

#include "AScreen.hpp"

void AScreen::draw()
{
    Raylibcpp::RayModel model;
    model.drawTexture(this->_background, 0, 0, RAYWHITE);
    this->drawText();
    this->drawButton();
}

void AScreen::run()
{
    this->draw();
    this->handleInput();
}

void AScreen::createButtons(std::string string, coord coord, Color color, int size, GameEvent screen)
{
    this->_buttonsScreen.emplace_back(string, coord, color, size, screen, this->_window);
}

void AScreen::createText(std::string string, coord coord, Color color, int size)
{
    this->_text.emplace_back(Raylibcpp::RayText(string, coord.x, coord.y, size, color));
}

void AScreen::drawButton(void)
{
    for (auto &button : this->_buttonsScreen) {
        Raylibcpp::RayModel model;
        Raylibcpp::RayText text(button.getString().c_str(), button.getCoord().x, button.getCoord().y, button.getSize(), button.getColor());
        button.update();
        model.drawRectangle(button.getCoord().x - 10, button.getCoord().y, button.getRectButton().width, button.getRectButton().height, button.getColorRect());
        text.drawText(text._string.c_str(), text._posX, text._posY, text._fontSize, text._color);
    }
}

void AScreen::drawText(void)
{
    for (auto &text : this->_text) {
        text.drawText(text._string.c_str(), text._posX, text._posY, text._fontSize, text._color);
    }
}