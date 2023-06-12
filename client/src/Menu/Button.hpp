/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <memory>
    #include "src/Core/Window.hpp"
    #include "encapsulation/Raylibcpp.hpp"

struct coord {
    float x;
    float y;
};

class Button {
    public:
        Button(std::string string, coord coord, Color color, int size, GameEvent screen, const std::shared_ptr<Window> &ptr);
        ~Button() = default;
        void update();
        void draw() {};
        void handleInput() {};
        void setCoord(coord coord);
        coord getCoord() const;
        void setString(std::string string);
        std::string getString() const;
        void setColor(Color color);
        Color getColor() const;
        void setSize(int size);
        int getSize() const;
        void setScreen(GameEvent screen);
        GameEvent getScreen() const;
        Rectangle getRectButton() const;
        Color getColorRect() const;
        bool getIsClicked() const;
        void setIsClicked(bool isClicked);
    private:
        std::shared_ptr<Window> _window;
        std::string _string;
        coord _coord;
        Color _colorFont;
        int _size;
        GameEvent _screen;
        Color _colorRect;
        bool _isClicked;
        bool _click;
        bool check;
        Rectangle _rectButton;
        Rectangle _mouse;
        Raylibcpp::RayMouse _rayMouse;
};

#endif /* !BUTTON_HPP_ */
