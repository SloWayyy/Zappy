/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
    #define DISPLAY_HPP_

    #include <memory>
    #include <map>
    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Character.hpp"
    #include "encapsulation/Raylibcpp.hpp"

class Display {
    public:
        Display() = default;
        Display(std::shared_ptr<Window> _window);
        ~Display() = default;
        void displayInformations(void);
        void run(std::map<std::size_t, Character>(_characters));
        void drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color);
    private:
        std::shared_ptr<Window> _window;
        Raylibcpp::RayText _rayText;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayWindow _rayWindow;
        std::map<std::size_t, std::size_t> _levelNbr;
};

#endif /* !DISPLAY_HPP_ */
