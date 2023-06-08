/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
    #define DISPLAY_HPP_

    #include <memory>
    #include "src/Core/Window.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Display {
    public:
        Display() = default;
        Display(std::shared_ptr<Window> _window);
        ~Display() = default;
        void run(void);
        void drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color);
    private:
        std::shared_ptr<Window> _window;
        Raylibcpp::RayText _rayText;
        Raylibcpp::RayWindow _rayWindow;
};

#endif /* !DISPLAY_HPP_ */
