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
    #include "src/Gameplay/Map.hpp"

class Display {
    public:
        Display() = default;
        Display(std::shared_ptr<Window> _window);
        ~Display() = default;
        void displayInformations(void);
        void run(std::map<std::size_t, std::shared_ptr<Character>>(_characters), std::shared_ptr<Map>);
        void drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color);
        void handleInput(void);
        std::size_t getTileX(void) const;
        std::size_t getTileY(void) const;
    private:
        std::shared_ptr<Window> _window;
        Raylibcpp::RayText _rayText;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayWindow _rayWindow;
        std::map<std::size_t, std::size_t> _levelNbr;
        std::size_t _height;
        std::size_t _width;
        std::size_t _x;
        std::size_t _y;
        std::map<std::pair<std::size_t, std::size_t>, std::array<int, 7>> _tile;
};

#endif /* !DISPLAY_HPP_ */
