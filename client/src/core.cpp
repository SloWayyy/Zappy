/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#include "core.hpp"

Core::Core()
{
    this->_window = std::shared_ptr<Window>(new Window(1920, 1080, 60));
    this->_menu = std::shared_ptr<Menu>(new Menu(this->_window));
    this->_gameplay = std::shared_ptr<Gameplay>(new Gameplay());
}

void Core::run(void)
{
    this->_gameplay->initPlayer();
    while (!this->_window->getExit()) {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        switch (this->_window->getGameEvent()) {
            case MENU:
                this->_window->run();
                this->_menu->run();
                break;
            case GAMEPLAY:
                BeginMode3D(this->_window->getCamera());
                this->_window->run();
                this->_gameplay->run();
                EndMode3D();
                break;
            case SETTINGS:
                this->_window->run();
                break;
            case TUTO:
                this->_window->run();
                break;
            case EXIT:
                this->_window->setExit(true);
        }
        EndDrawing();
    }
}
