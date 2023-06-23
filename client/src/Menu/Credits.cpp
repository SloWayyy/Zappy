/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Credits.cpp
*/

#include "Credits.hpp"

Credits::Credits(std::shared_ptr<Window> window)
{
    this->_window = window;
    width = this->_window->getScreenWidth();
    height = this->_window->getScreenHeight();
    try {
        this->_img.insert(std::make_pair(1, this->_rayModel.loadTexture("client/assets/menu/mixamo.png")));
        this->_img.insert(std::make_pair(2, this->_rayModel.loadTexture("client/assets/menu/blender.png")));
        this->_img.insert(std::make_pair(3, this->_rayModel.loadTexture("client/assets/menu/sketch.png")));
        this->_members.insert(std::make_pair(1, this->_rayModel.loadTexture("client/assets/menu/Member/kevin.png")));
        this->_members.insert(std::make_pair(2, this->_rayModel.loadTexture("client/assets/menu/Member/taha.png")));
        this->_members.insert(std::make_pair(3, this->_rayModel.loadTexture("client/assets/menu/Member/mehdi.png")));
        this->_members.insert(std::make_pair(4, this->_rayModel.loadTexture("client/assets/menu/Member/florian.png")));
        this->_members.insert(std::make_pair(5, this->_rayModel.loadTexture("client/assets/menu/Member/jonathan.png")));
        this->_members.insert(std::make_pair(6, this->_rayModel.loadTexture("client/assets/menu/Member/rayan.png")));
        createButtons("BACK", {width / 50.0f, height / 30.0f}, GOLD, 50, MENU);
        createText("Ressources:", {width / 50.0f, height / 10.0f}, RAYWHITE, 50);
        createText("Mixamo", {width / 50.0f + 200, height / 3.0f - 100}, RED, 40);
        createText("Blender", {width / 2.0f + 300, height / 3.0f - 100}, RED, 50);
        createText("Sketchfab", {width / 2.0f + 950, height / 3.0f - 100}, RED, 40);
        createText("Made by:", {width / 50.0f, height / 2.8f - 100}, RAYWHITE, 50);
        createText("Kevin.N / Taha.A / Mehdi.D / Florian.L / Jonathan.Y / Rayan.E", {width / 50.0f + 100, height / 2.0f - 100}, DARKBLUE, 50);
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Credits constructor failed");
    }
}

Credits::~Credits()
{
    for (auto &img : _img)
        this->_rayModel.unloadTexture(img.second);
    for (auto &members : _members)
        this->_rayModel.unloadTexture(members.second);
}

void Credits::handleInput()
{
    for (auto &img: _img) {
        (img.first == 1) ? this->_rayModel.drawTexture(img.second, width / 50.0f + 150, height / 7.0f, SKYBLUE)
        : (img.first == 2) ? this->_rayModel.drawTexture(img.second, width / 2.0f + 250, height / 7.0f, SKYBLUE)
        : this->_rayModel.drawTexture(img.second, width / 2.0f + 950, height / 7.0f, SKYBLUE);
    }
    for (auto &members : _members) {
        (members.first == 1) ? this->_rayModel.drawTexture(members.second, width / 50.0f + 175, height / 2.0f - 250, SKYBLUE)
        : (members.first == 2) ? this->_rayModel.drawTexture(members.second, width / 50.0f + 425, height / 2.0f - 250, SKYBLUE)
        : (members.first == 3) ? this->_rayModel.drawTexture(members.second, width / 50.0f + 675, height / 2.0f - 250, SKYBLUE)
        : (members.first == 4) ? this->_rayModel.drawTexture(members.second, width / 50.0f + 950, height / 2.0f - 250, SKYBLUE)
        : (members.first == 5) ? this->_rayModel.drawTexture(members.second, width / 50.0f + 1300, height / 2.0f - 250, SKYBLUE)
        : this->_rayModel.drawTexture(members.second, width / 50.0f + 1600, height / 2.0f - 250, SKYBLUE);
    }
}
