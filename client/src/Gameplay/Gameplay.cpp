/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#include "src/Gameplay/Gameplay.hpp"

Gameplay::Gameplay(std::shared_ptr<Window> _window) : _window(_window), _map(Map(10, 10)), _currentCharacterId(0), _currentCharacterIndex(0)
{
}

void Gameplay::initPlayer(Vector3 pos)
{
    Character player(0, 0, pos);

    _characters.push_back(player);
}

void Gameplay::runPlayers(void)
{
    for (auto &character : this->_characters) {
        character.run();
    }
}

void Gameplay::drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color)
{
    this->_rayWindow.endMode3D();
    this->_rayText.drawText(text, posX, posY, fontSize, color);
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Gameplay::run(void)
{
    this->_map.run();
    this->drawTextOnScreen("F1:  Camera 1", 20, this->_window->getScreenHeight() - 150, 10, BLACK);
    this->drawTextOnScreen("F2: Camera 2", 20, this->_window->getScreenHeight() - 150, 60, BLACK);
    this->drawTextOnScreen("F3: Camera 3", 20, this->_window->getScreenHeight() - 150, 110, BLACK);
    this->handleInput();
    this->runPlayers();
}

void Gameplay::setCurrentCharacter()
{
    if (this->_currentCharacterId >= this->_characters.size())
        this->_currentCharacterId = 0;
    for (std::size_t i = 0; i < this->_characters.size(); i++) {
        if (this->_currentCharacterId == i) {
            this->_currentCharacter = this->_characters[i];
            this->_currentCharacterId++;
            break;
        }
    }
}

void Gameplay::handleInput(void)
{
    if (this->_rayWindow.isKeyDown(KEY_ESCAPE))
        this->_window->setExit(true);
    if (this->_rayWindow.isKeyReleased(KEY_F1)) {
        this->setCurrentCharacter();
        this->_window->setCamera({_currentCharacter.getPosition().x, _currentCharacter.getPosition().y + (float)1.5, _currentCharacter.getPosition().z - (float)0.5}, { 10.0f, 2.0f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
    }
    if (this->_rayWindow.isKeyReleased(KEY_F2)) {
        this->setCurrentCharacter();
        this->_window->setCamera({_currentCharacter.getPosition().x, _currentCharacter.getPosition().y + (float)3.5, _currentCharacter.getPosition().z - (float)3.5}, { 0.6f, -4.5f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
    }
    if (this->_rayWindow.isKeyReleased(KEY_F3)) {
        this->_window->setCamera({ -5.0f, 15.0f, 10.0f }, { 10.0f, 2.0f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 80.0f, CAMERA_PERSPECTIVE);
    }
}
