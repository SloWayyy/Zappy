/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#include "Menu/include/menu.hpp"

Menu::Menu()
{
    this->nbButton = 0;
}

void Menu::init()
{
    this->_background = LoadTexture("assets/menu/background_menu.png");
    createButtons("PLAY", {(float)this->getScreenWidth() / 15.0f, this->getScreenHeight() / 12.0f}, GOLD, 100, GAMEPLAY);
    createButtons("HOW TO PLAY", {(float)this->getScreenWidth() / 15.0f, this->getScreenHeight() / 5.0f}, GOLD, 100, TUTO);
    createButtons("EXIT", {(float)this->getScreenWidth() / 15.0f, this->getScreenHeight() / 3.0f}, GOLD, 100, EXIT);
    createButtons("SETTINGS", {(float)this->getScreenWidth() / 15.0f, this->getScreenHeight() / 1.5f}, GOLD, 100, SETTINGS);
}

void Menu::draw()
{
    this->drawTexture(this->_background, 0, 0, RAYWHITE);
    this->drawButton();
}

void Menu::handleInput()
{
}

void Menu::stop()
{
    UnloadTexture(this->_background);
}

void Menu::run()
{
    this->draw();
    this->handleInput();
}

buttons::buttons(std::string string, coord_t coord, int nbButton, Color color, int size, GameEvent screen)
{
    this->setString(string);
    this->setCoord(coord);
    this->setColor(color);
    this->setSize(size);
    this->setNbButton(nbButton);
    this->setScreen(screen);
    this->_colorRect = BLUE;
    this->_isClicked = false;
    this->_saveColorRect = _colorRect;
    this->_rectButton.x = this->getCoord().x;
    this->_rectButton.y = this->getCoord().y;
    this->_rectButton.width = this->getString().size() * this->getSize();
    this->_rectButton.height = 100;
}

void buttons::update()
{
    static bool check = false;
    static bool _click = false;
    this->_color = this->_color;
    this->_colorRect = _saveColorRect;
    this->_mouse.x = GetMouseX();
    this->_mouse.y = GetMouseY();
    bool collision = CheckCollisionRecs(this->_mouse, this->_rectButton);

    if (collision) {
        if (IsMouseButtonDown(0) == true) {
            this->_color = GOLD;
            this->_colorRect = PURPLE;
            _click = true;
        } else {
            check = true;
            this->_color = BLUE;
            this->_colorRect = GOLD;
        }
    }
    if (check == true && collision == false) {
        this->_color = GOLD;
        this->_colorRect = BLUE;
    }
    if (_click == true && IsMouseButtonReleased(0) == true) {
        this->_isClicked = true;
        check = false;
        _click = false;
    }
}

void Menu::createButtons(std::string string, coord_t coord, Color color, int size, GameEvent screen)
{
    // buttons tmpButton(string, coord, this->nbButton, color, size, screen);

    this->_buttonsScreen.emplace_back(string, coord, this->nbButton, color, size, screen);
    this->nbButton++;
}

void Menu::drawButton(void)
{
    for (auto &button : this->_buttonsScreen) {
        button.update();
        this->_text.drawRectangle(button.getCoord().x - 10, button.getCoord().y, button.getRectButton().width, button.getRectButton().height, button.getColorRect());
        this->_text.drawText(button.getString().c_str(), button.getCoord().x, button.getCoord().y, button.getSize(), button.getColor());
        // printf("before : %p, %d\n", this, button.getScreen());
        if (button.getIsClicked() == true) {
            // printf("after : %p, %d\n", this, button.getScreen());
            this->setGameEvent(button.getScreen());
            button.setIsClicked(false);
            break;
        }
    }
}
