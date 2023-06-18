/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setting.cpp
*/

#include "Setting.hpp"

Setting::Setting(std::shared_ptr<Window> window) : _volume(50), _fps(60)
{
    try {
        this->_window = window;
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu.png");
        createButtons("BACK", {this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 30.0f}, GOLD, 50, MENU);
        createText("SETTINGS", {this->_window->getScreenWidth() / 1.5f, this->_window->getScreenHeight() / 30.0f}, RED, 100);
        createText("Volumes :", {this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 10.0f}, RAYWHITE, 50);
        createText(std::to_string(_volume), {this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 7.5f}, RAYWHITE, 50);
        createButtons("-", {this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
        createButtons("+", {this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
        createText("FPS :", {this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 5.0f}, RAYWHITE, 50);
        createText(std::to_string(_fps), {this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 4.0f}, RAYWHITE, 50);
        createButtons("<", {this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 4.0f}, PINK, 50, SETTINGS);
        createButtons(">", {this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 4.0f}, PINK, 50, SETTINGS);
        createText("Météo :", {this->_window->getScreenWidth() / 50.0f, this->_window->getScreenHeight() / 3.0f}, RAYWHITE, 50);
        createText("Jour", {this->_window->getScreenWidth() / 3.0f, this->_window->getScreenHeight() / 2.5f}, RAYWHITE, 50);
        createButtons("<", {this->_window->getScreenWidth() / 5.0f, this->_window->getScreenHeight() / 2.5f}, PINK, 50, SETTINGS);
        createButtons(">", {this->_window->getScreenWidth() / 2.0f, this->_window->getScreenHeight() / 2.5f}, PINK, 50, SETTINGS);
        createText("Select Key for :", {this->_window->getScreenWidth() / 1.5f, this->_window->getScreenHeight() / 10.0f}, BLACK, 50);
        createText("Cam 1:", {this->_window->getScreenWidth() / 1.6f, this->_window->getScreenHeight() / 7.5f}, BLACK, 50);
        createButtons("<", {this->_window->getScreenWidth() / 1.3f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
        createText(this->_window->keyToString(this->_window->getKeyCam1()), {this->_window->getScreenWidth() / 1.15f, this->_window->getScreenHeight() / 7.5f}, BLACK, 50);
        createButtons(">", {this->_window->getScreenWidth() / 1.0f, this->_window->getScreenHeight() / 7.5f}, PINK, 50, SETTINGS);
        createText("Cam 2:", {this->_window->getScreenWidth() / 1.6f, this->_window->getScreenHeight() / 5.0f}, BLACK, 50);
        createButtons("<", {this->_window->getScreenWidth() / 1.3f, this->_window->getScreenHeight() / 5.0f}, PINK, 50, SETTINGS);
        createText(this->_window->keyToString(this->_window->getKeyCam2()), {this->_window->getScreenWidth() / 1.15f, this->_window->getScreenHeight() / 5.0f}, BLACK, 50);
        createButtons(">", {this->_window->getScreenWidth() / 1.0f, this->_window->getScreenHeight() / 5.0f}, PINK, 50, SETTINGS);
        createText("Cam 3:", {this->_window->getScreenWidth() / 1.6f, this->_window->getScreenHeight() / 3.0f}, BLACK, 50);
        createButtons("<", {this->_window->getScreenWidth() / 1.3f, this->_window->getScreenHeight() / 3.0f}, PINK, 50, SETTINGS);
        createText(this->_window->keyToString(this->_window->getKeyCam3()), {this->_window->getScreenWidth() / 1.15f, this->_window->getScreenHeight() / 3.0f}, BLACK, 50);
        createButtons(">", {this->_window->getScreenWidth() / 1.0f, this->_window->getScreenHeight() / 3.0f}, PINK, 50, SETTINGS);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Setting constructor failed");
    }
}

Setting::~Setting()
{
    this->_rayModel.unloadTexture(this->_background);
}

void Setting::handleInput()
{
    int x = this->_rayMouse.getMouseX();
    int y = this->_rayMouse.getMouseY();
    if (this->_rayMouse.isMouseButtonPressed(0) == true) {
        if (this->_buttonsScreen[1].MouseClickedOnButton(x, y) == true) {
            if (this->_volume > 0)
                this->_volume -= 5;
            this->_text[2]._string = std::to_string(_volume);
            this->_Raymusic.setMusicVolume(this->_window->getMusic(), (this->_volume / 100.0));
        }
        if (this->_buttonsScreen[2].MouseClickedOnButton(x, y) == true) {
            if (this->_volume < 100)
                this->_volume += 5;
            this->_text[2]._string = std::to_string(_volume);
            this->_Raymusic.setMusicVolume(this->_window->getMusic(), (this->_volume / 100.0));
        }
        if (this->_buttonsScreen[3].MouseClickedOnButton(x, y) == true) {
            (this->_fps > 30) ? (this->_fps /= 2) : (this->_fps = 120);
            this->_text[4]._string = std::to_string(_fps);
            this->_window->setFps(_fps);
            this->_rayWindow.setTargetFPS(_fps);
        }
        if (this->_buttonsScreen[4].MouseClickedOnButton(x, y) == true) {
            (this->_fps < 120) ? (this->_fps *= 2) : (this->_fps = 30);
            this->_text[4]._string = std::to_string(_fps);
            this->_window->setFps(_fps);
            this->_rayWindow.setTargetFPS(_fps);
        }
        if (this->_buttonsScreen[5].MouseClickedOnButton(x, y) == true) {
            (this->_text[6]._string == "Jour") ? (this->_text[6]._string = "Nuit", this->_window->setIsNight(true), this->_window->setIsChanged(true))
            : (this->_text[6]._string = "Jour", this->_window->setIsNight(false), this->_window->setIsChanged(true));
        }
        if (this->_buttonsScreen[6].MouseClickedOnButton(x, y) == true) {
            (this->_text[6]._string == "Jour") ? (this->_text[6]._string = "Nuit", this->_window->setIsNight(true), this->_window->setIsChanged(true))
            : (this->_text[6]._string = "Jour", this->_window->setIsNight(false), this->_window->setIsChanged(true));
        }
        if (this->_buttonsScreen[7].MouseClickedOnButton(x, y) == true) {
            (this->_window->getKeyCam1() == KEY_F1) ? (this->_window->setKeyCam1(KEY_X), this->_text[9]._string = "X")
            : (this->_window->getKeyCam1() == KEY_X) ? (this->_window->setKeyCam1(KEY_K), this->_text[9]._string = "K")
            : (this->_window->setKeyCam1(KEY_F1), this->_text[9]._string = "F1");
        }
        if (this->_buttonsScreen[8].MouseClickedOnButton(x, y) == true) {
            (this->_window->getKeyCam1() == KEY_F1) ? (this->_window->setKeyCam1(KEY_K), this->_text[9]._string = "K")
            : (this->_window->getKeyCam1() == KEY_K) ? (this->_window->setKeyCam1(KEY_X), this->_text[9]._string = "X")
            : (this->_window->setKeyCam1(KEY_F1), this->_text[9]._string = "F1");
        }
        if (this->_buttonsScreen[9].MouseClickedOnButton(x, y) == true) {
            (this->_window->getKeyCam2() == KEY_F2) ? (this->_window->setKeyCam2(KEY_C), this->_text[11]._string = "C")
            : (this->_window->getKeyCam2() == KEY_C) ? (this->_window->setKeyCam2(KEY_L), this->_text[11]._string = "L")
            : (this->_window->setKeyCam2(KEY_F2), this->_text[11]._string = "F2");
        }
        if (this->_buttonsScreen[10].MouseClickedOnButton(x, y) == true) {
            (this->_window->getKeyCam2() == KEY_F2) ? (this->_window->setKeyCam2(KEY_L), this->_text[11]._string = "L")
            : (this->_window->getKeyCam2() == KEY_L) ? (this->_window->setKeyCam2(KEY_C), this->_text[11]._string = "C")
            : (this->_window->setKeyCam2(KEY_F2), this->_text[11]._string = "F2");
        }
        if (this->_buttonsScreen[11].MouseClickedOnButton(x, y) == true) {
            (this->_window->getKeyCam3() == KEY_F3) ? (this->_window->setKeyCam3(KEY_V), this->_text[13]._string = "V")
            : (this->_window->getKeyCam3() == KEY_V) ? (this->_window->setKeyCam3(KEY_F), this->_text[13]._string = "F")
            : (this->_window->setKeyCam3(KEY_F3), this->_text[13]._string = "F3");
        }
        if (this->_buttonsScreen[12].MouseClickedOnButton(x, y) == true) {
            (this->_window->getKeyCam3() == KEY_F3) ? (this->_window->setKeyCam3(KEY_F), this->_text[13]._string = "F")
            : (this->_window->getKeyCam3() == KEY_F) ? (this->_window->setKeyCam3(KEY_V), this->_text[13]._string = "V")
            : (this->_window->setKeyCam3(KEY_F3), this->_text[13]._string = "F3");
        }
    }
}
