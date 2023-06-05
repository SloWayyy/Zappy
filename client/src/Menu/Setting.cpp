/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setting.cpp
*/

#include "Setting.hpp"

Setting::Setting(std::shared_ptr<Window> window) : _volume(50), _fps(60)
{
    this->_window = window;
    this->_background = LoadTexture("assets/menu/background_menu.png");
    createButtons("BACK", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 30.0f}, GOLD, 50, MENU);
    createText("SETTINGS", {(float)this->_window->getScreenWidth() / 1.5f, this->_window->getScreenHeight() / 30.0f}, RED, 100);
    createText("Volumes :", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 10.0f}, RAYWHITE, 50);
    createText(std::to_string(_volume), {(float)this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 7.5f}, RAYWHITE, 50);
    createButtons("-", {(float)this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
    createButtons("+", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
    createText("FPS :", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 5.0f}, RAYWHITE, 50);
    createText(std::to_string(_fps), {(float)this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 4.0f}, RAYWHITE, 50);
    createButtons("<", {(float)this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 4.0f}, PINK, 50, SETTINGS);
    createButtons(">", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 4.0f}, PINK, 50, SETTINGS);
    createText("Météo :", {(float)this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 3.0f}, RAYWHITE, 50);
    createText("Jour", {(float)this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 2.5f}, RAYWHITE, 50);
    createButtons("<", {(float)this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 2.5f}, PINK, 50, SETTINGS);
    createButtons(">", {(float)this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 2.5f}, PINK, 50, SETTINGS);
}

void Setting::handleInput()
{
    int x = this->_rayMouse.getMouseX();
    int y = this->_rayMouse.getMouseY();
    if (this->_rayMouse.isMouseButtonPressed(0) == true) {
        if (x >= this->_buttonsScreen[1].getCoord().x && x <= this->_buttonsScreen[1].getCoord().x + this->_buttonsScreen[1].getRectButton().width && y >= this->_buttonsScreen[1].getCoord().y && y <= this->_buttonsScreen[1].getCoord().y + this->_buttonsScreen[1].getRectButton().height) {
            if (this->_volume > 0)
                this->_volume -= 5;
            this->_text[2]._string = std::to_string(_volume);
        }
        if (x >= this->_buttonsScreen[2].getCoord().x && x <= this->_buttonsScreen[2].getCoord().x + this->_buttonsScreen[2].getRectButton().width && y >= this->_buttonsScreen[2].getCoord().y && y <= this->_buttonsScreen[2].getCoord().y + this->_buttonsScreen[2].getRectButton().height) {
            if (this->_volume < 100)
                this->_volume += 5;
            this->_text[2]._string = std::to_string(_volume);
        }
        if (x >= this->_buttonsScreen[3].getCoord().x && x <= this->_buttonsScreen[3].getCoord().x + this->_buttonsScreen[3].getRectButton().width && y >= this->_buttonsScreen[3].getCoord().y && y <= this->_buttonsScreen[3].getCoord().y + this->_buttonsScreen[3].getRectButton().height) {
            if (this->_fps > 30)
                this->_fps /= 2;
            else
                this->_fps = 120;
            this->_text[4]._string = std::to_string(_fps);
        }
        if (x >= this->_buttonsScreen[4].getCoord().x && x <= this->_buttonsScreen[4].getCoord().x + this->_buttonsScreen[4].getRectButton().width && y >= this->_buttonsScreen[4].getCoord().y && y <= this->_buttonsScreen[4].getCoord().y + this->_buttonsScreen[4].getRectButton().height) {
            if (this->_fps < 120)
                this->_fps *= 2;
            else
                this->_fps = 30;
            this->_text[4]._string = std::to_string(_fps);
        }
        if (x >= this->_buttonsScreen[5].getCoord().x && x <= this->_buttonsScreen[5].getCoord().x + this->_buttonsScreen[5].getRectButton().width && y >= this->_buttonsScreen[5].getCoord().y && y <= this->_buttonsScreen[5].getCoord().y + this->_buttonsScreen[5].getRectButton().height) {
            if (this->_text[6]._string == "Jour")
                this->_text[6]._string = "Nuit";
            else
                this->_text[6]._string = "Jour";
        }
        if (x >= this->_buttonsScreen[6].getCoord().x && x <= this->_buttonsScreen[6].getCoord().x + this->_buttonsScreen[6].getRectButton().width && y >= this->_buttonsScreen[6].getCoord().y && y <= this->_buttonsScreen[6].getCoord().y + this->_buttonsScreen[6].getRectButton().height) {
            if (this->_text[6]._string == "Jour")
                this->_text[6]._string = "Nuit";
            else
                this->_text[6]._string = "Jour";
        }
    }

}