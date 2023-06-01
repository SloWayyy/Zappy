/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <memory>
    #include "Window.hpp"
    #include "encapsulation/Raylibcpp.hpp"

typedef struct coord {
    float x;
    float y;
} coord_t;

class Button {
    public:
        Button(std::string string, coord_t coord, Color color, int size, GameEvent screen, const std::shared_ptr<Window> &ptr);
        ~Button() = default;
        void update();
        void draw() {};
        void handleInput() {};
        void setCoord(coord_t coord);
        coord_t getCoord() const;
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
        coord_t _coord;
        std::string _string;
        Color _colorFont;
        bool _click;
        bool check;
        int _size;
        bool _isClicked;
        GameEvent _screen;
        Rectangle _rectButton;
        Color _colorRect;
        Rectangle _mouse;
        std::shared_ptr<Window> _window;
};

#endif /* !BUTTON_HPP_ */
