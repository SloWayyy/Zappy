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
        this->_mixamo = this->_rayModel.loadTexture("client/assets/menu/mixamo.png");
        this->_blender = this->_rayModel.loadTexture("client/assets/menu/blender.png");
        this->_sketchfab = this->_rayModel.loadTexture("client/assets/menu/sketch.png");
        this->_kevin = this->_rayModel.loadTexture("client/assets/menu/Member/kevin.png");
        this->_taha = this->_rayModel.loadTexture("client/assets/menu/Member/taha.png");
        this->_mehdi = this->_rayModel.loadTexture("client/assets/menu/Member/mehdi.png");
        this->_florian = this->_rayModel.loadTexture("client/assets/menu/Member/florian.png");
        this->_jonathan = this->_rayModel.loadTexture("client/assets/menu/Member/jonathan.png");
        this->_rayan = this->_rayModel.loadTexture("client/assets/menu/Member/rayan.png");
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
    this->_rayModel.unloadTexture(this->_mixamo);
    this->_rayModel.unloadTexture(this->_blender);
    this->_rayModel.unloadTexture(this->_sketchfab);
    this->_rayModel.unloadTexture(this->_kevin);
    this->_rayModel.unloadTexture(this->_taha);
    this->_rayModel.unloadTexture(this->_mehdi);
    this->_rayModel.unloadTexture(this->_florian);
    this->_rayModel.unloadTexture(this->_jonathan);
    this->_rayModel.unloadTexture(this->_rayan);
}

void Credits::handleInput()
{
    this->_rayModel.drawTexture(this->_mixamo, width / 50.0f + 150, height / 7.0f, SKYBLUE);
    this->_rayModel.drawTexture(this->_blender, width / 2.0f + 250, height / 7.0f, SKYBLUE);
    this->_rayModel.drawTexture(this->_sketchfab, width / 2.0f + 950, height / 7.0f, SKYBLUE);
    this->_rayModel.drawTexture(this->_kevin, width / 50.0f + 175, height / 2.0f - 250, SKYBLUE);
    this->_rayModel.drawTexture(this->_taha, width / 50.0f + 425, height / 2.0f - 250, SKYBLUE);
    this->_rayModel.drawTexture(this->_mehdi, width / 50.0f + 675, height / 2.0f - 250, SKYBLUE);
    this->_rayModel.drawTexture(this->_florian, width / 50.0f + 950, height / 2.0f - 250, SKYBLUE);
    this->_rayModel.drawTexture(this->_jonathan, width / 50.0f + 1300, height / 2.0f - 250, SKYBLUE);
    this->_rayModel.drawTexture(this->_rayan, width / 50.0f + 1600, height / 2.0f - 250, SKYBLUE);
}