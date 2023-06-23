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
        std::size_t width = this->_window->getScreenWidth();
        std::size_t height = this->_window->getScreenHeight();
        this->_background = this->_rayModel.loadTexture("client/assets/menu/background_menu.png");
        createButtons("BACK", {width / 50.0f, height / 30.0f}, GOLD, 50, MENU);
        createText("SETTINGS", {width / 1.5f, height / 30.0f}, RED, 100);
        createText("Volumes :", {width / 50.0f, height / 10.0f}, BLACK, 50);
        createText(std::to_string(_volume), {width / 3.0f, height / 7.5f}, BLACK, 50);
        createButtons("-", {width / 5.0f, height / 7.5f}, PINK, 50, SETTINGS);
        createButtons("+", {width / 2.0f, height / 7.5f}, PINK, 50, SETTINGS);
        createText("FPS :", {width / 50.0f, height / 5.0f}, BLACK, 50);
        createText(std::to_string(_fps), {width / 3.0f, height / 4.0f}, BLACK, 50);
        createButtons("<", {width / 5.0f, height / 4.0f}, PINK, 50, SETTINGS);
        createButtons(">", {width / 2.0f, height / 4.0f}, PINK, 50, SETTINGS);
        createText("Météo :", {width / 50.0f, height / 3.0f}, BLACK, 50);
        createText("Jour", {width / 3.0f, height / 2.5f}, BLACK, 50);
        createButtons("<", {width / 5.0f, height / 2.5f}, PINK, 50, SETTINGS);
        createButtons(">", {width / 2.0f, height / 2.5f}, PINK, 50, SETTINGS);
        createText("Select Key for :", {width / 1.5f, height / 10.0f}, BLACK, 50);
        createText("Cam 1:", {width / 1.6f, height / 7.5f}, BLACK, 50);
        createButtons("<", {width / 1.3f, height / 7.5f}, PINK, 50, SETTINGS);
        createText(this->_window->keyToString(this->_window->getKeyCam1()), {width / 1.15f, height / 7.5f}, BLACK, 50);
        createButtons(">", {width / 1.0f, height / 7.5f}, PINK, 50, SETTINGS);
        createText("Cam 2:", {width / 1.6f, height / 5.0f}, BLACK, 50);
        createButtons("<", {width / 1.3f, height / 5.0f}, PINK, 50, SETTINGS);
        createText(this->_window->keyToString(this->_window->getKeyCam2()), {width / 1.15f, height / 5.0f}, BLACK, 50);
        createButtons(">", {width / 1.0f, height / 5.0f}, PINK, 50, SETTINGS);
        createText("Cam 3:", {width / 1.6f, height / 3.0f}, BLACK, 50);
        createButtons("<", {width / 1.3f, height / 3.0f}, PINK, 50, SETTINGS);
        createText(this->_window->keyToString(this->_window->getKeyCam3()), {width / 1.15f, height / 3.0f}, BLACK, 50);
        createButtons(">", {width / 1.0f, height / 3.0f}, PINK, 50, SETTINGS);
        createText("Music :", {width / 1.6f, height / 2.5f}, BLACK, 50);
        createButtons("<", {width / 1.3f, height / 2.5f}, PINK, 50, SETTINGS);
        createText("1", {width / 1.15f, height / 2.5f}, BLACK, 50);
        createButtons(">", {width / 1.0f, height / 2.5f}, PINK, 50, SETTINGS);
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
        if (this->_buttonsScreen[13].MouseClickedOnButton(x, y) == true) {
            this->_text[15]._string = (this->_text[15]._string == "1") ? "2" : "1";
            this->_window->setMusic((this->_text[15]._string == "1") ? this->_window->getMusics()[1] : this->_window->getMusics()[2]);
            this->_Raymusic.stopMusicStream((this->_text[15]._string == "1") ? this->_window->getMusics()[2] : this->_window->getMusics()[1]);
            this->_Raymusic.playMusicStream((this->_text[15]._string == "1") ? this->_window->getMusics()[1] : this->_window->getMusics()[2]);
        }
        if (this->_buttonsScreen[14].MouseClickedOnButton(x, y) == true) {
            this->_text[15]._string = (this->_text[15]._string == "1") ? "2" : "1";
            this->_window->setMusic((this->_text[15]._string == "1") ? this->_window->getMusics()[1] : this->_window->getMusics()[2]);
            this->_Raymusic.stopMusicStream((this->_text[15]._string == "1") ? this->_window->getMusics()[2] : this->_window->getMusics()[1]);
            this->_Raymusic.playMusicStream((this->_text[15]._string == "1") ? this->_window->getMusics()[1] : this->_window->getMusics()[2]);
        }
    }
}
