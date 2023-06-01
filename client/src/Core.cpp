/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** core
*/

#include "Core.hpp"

Core::Core(): _window(std::make_shared<Window>(1920, 1080, 60)), _menu(std::make_shared<Menu>(this->_window)), _gameplay(std::make_shared<Gameplay>(this->_window))
{
}

void Core::run(void)
{
    this->_gameplay->initPlayer({0, 1.1, 2});
    this->_gameplay->initPlayer({0, 1.1, 4});
    this->_gameplay->initPlayer({0, 1.1, 6});
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
