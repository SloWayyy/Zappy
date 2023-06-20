/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Display
*/

#include "Display.hpp"

Display::Display(std::shared_ptr<Window> _window) : _window(_window), _height(0), _width(0), _x(0), _y(0)
{
}

void Display::drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color)
{
    this->_rayWindow.endMode3D();
    this->_rayText.drawText(text, posX, posY, fontSize, color);
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Display::displayInformations(void)
{
    std::size_t height = this->_window->getScreenHeight();
    std::size_t width = this->_window->getScreenWidth();

    this->_rayWindow.endMode3D();
    this->_rayModel.drawRectangle(height - (height / 7.5), 0, height / 7.5, width, {130, 130, 130, 200});
    this->_rayText.drawText("Level 1: " + std::to_string(this->_levelNbr[1]), height - (height / 8), (width - 1000), 40, BLACK);
    this->_rayText.drawText("Level 2: " + std::to_string(this->_levelNbr[2]), height - (height / 8), (width - 880), 40, BLACK);
    this->_rayText.drawText("Level 3: " + std::to_string(this->_levelNbr[3]), height - (height / 8), (width - 760), 40, BLACK);
    this->_rayText.drawText("Level 4: " + std::to_string(this->_levelNbr[4]), height - (height / 8), (width - 640), 40, BLACK);
    this->_rayText.drawText("Level 5: " + std::to_string(this->_levelNbr[5]), height - (height / 8), (width - 520), 40, BLACK);
    this->_rayText.drawText("Level 6: " + std::to_string(this->_levelNbr[6]), height - (height / 8), (width - 400), 40, BLACK);
    this->_rayText.drawText("Level 7: " + std::to_string(this->_levelNbr[7]), height - (height / 8), (width - 280), 40, BLACK);
    this->_rayText.drawText("Level 8: " + std::to_string(this->_levelNbr[8]), height - (height / 8), (width - 160), 40, BLACK);
    this->_rayText.drawText("Tile: " + std::to_string(this->_x) + " - " + std::to_string(this->_y), height - (height) + 50, (width - 1000), 40, BLACK);
    this->_rayText.drawText("Food: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][0]), height - (height) + 50, (width - 880), 40, BLACK);
    this->_rayText.drawText("Linemate: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][1]), height - (height) + 50, (width - 760), 40, BLACK);
    this->_rayText.drawText("Deraumere: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][2]), height - (height) + 50, (width - 640), 40, BLACK);
    this->_rayText.drawText("Sibur: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][3]), height - (height) + 50, (width - 520), 40, BLACK);
    this->_rayText.drawText("Mendiane: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][4]), height - (height) + 50, (width - 400), 40, BLACK);
    this->_rayText.drawText("Phiras: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][5]), height - (height) + 50, (width - 280), 40, BLACK);
    this->_rayText.drawText("Thystame: " + std::to_string(this->_tile[std::make_pair(this->_x, this->_y)][6]), height - (height) + 50, (width - 160), 40, BLACK);
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Display::run(std::map<std::size_t, std::shared_ptr<Character>>(_characters), std::shared_ptr<Map> map)
{
    this->_height = map->getheight();
    this->_width = map->getwidth();
    this->_tile = map->getMapInventory();
    this->drawTextOnScreen("DISPLAY MODE", 40, (this->_window->getScreenHeight() / 2) - 100, 10, BLACK);
    this->_levelNbr[1] = 0;
    this->_levelNbr[2] = 0;
    this->_levelNbr[3] = 0;
    this->_levelNbr[4] = 0;
    this->_levelNbr[5] = 0;
    this->_levelNbr[6] = 0;
    this->_levelNbr[7] = 0;
    this->_levelNbr[8] = 0;
    for (auto &Character : _characters)
        this->_levelNbr[Character.second->getLevel()] += 1;
    this->handleInput();
    this->displayInformations();
}

void Display::handleInput(void)
{
    if (IsKeyPressed(KEY_RIGHT))
        this->_x = (this->_x + 1 > this->_width - 1) ? 0 : this->_x + 1;
    if (IsKeyPressed(KEY_LEFT))
        this->_x = (this->_x == 0) ? this->_width - 1 : this->_x - 1;
    if (IsKeyPressed(KEY_UP))
        this->_y = (this->_y == 0) ? this->_height - 1 : this->_y - 1;
    if (IsKeyPressed(KEY_DOWN))
        this->_y = (this->_y + 1 > this->_height - 1) ? 0 : this->_y + 1;
}

std::size_t Display::getTileX(void) const
{
    return (this->_x);
}

std::size_t Display::getTileY(void) const
{
    return (this->_y);
}
