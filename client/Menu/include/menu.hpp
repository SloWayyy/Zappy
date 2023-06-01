/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <vector>
    #include "Button.hpp"
    #include "Window.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Menu {
    public:
        Menu(std::shared_ptr<Window> _window);
        ~Menu() = default;
        void drawButton();
        void run();
        void draw();
        void handleInput();
        void createButtons(std::string string, coord_t coord, Color color, int size, GameEvent screen);
    protected:
    private:
        Texture2D _background;
        // Raylibcpp::Text _text;
        std::vector<Button> _buttonsScreen;
        std::shared_ptr<Window> _window;
};

#endif /* !MENU_HPP_ */
