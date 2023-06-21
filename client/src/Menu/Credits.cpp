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
        createButtons("BACK", {width / 50.0f, height / 30.0f}, GOLD, 50, MENU);
        createText("Ressources:", {width / 50.0f, height / 10.0f}, RAYWHITE, 50);
        createText("https://www.mixamo.com/", {width / 50.0f + 50, height / 3.0f + 100}, RED, 40);
        createText("Blender", {width / 2.0f + 300, height / 3.0f + 100}, RED, 50);
        createText("https://sketchfab.com/", {width / 2.0f + 800, height / 3.0f + 100}, RED, 40);
        createText("Made by:", {width / 50.0f, height / 2.2f}, RAYWHITE, 50);
        createText("Kevin.N / Taha.A / Mehdi.D / Florian.L / Jonathan.Y / Rayan.E", {width / 50.0f + 50, height / 2.0f}, DARKBLUE, 50);
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
}

void Credits::handleInput()
{
    this->_rayModel.drawTexture(this->_mixamo, width / 50.0f + 150, height / 7.0f + 100, SKYBLUE);
    this->_rayModel.drawTexture(this->_blender, width / 2.0f + 250, height / 7.0f + 100, SKYBLUE);
    this->_rayModel.drawTexture(this->_sketchfab, width / 2.0f + 950, height / 7.0f + 100, SKYBLUE);
}