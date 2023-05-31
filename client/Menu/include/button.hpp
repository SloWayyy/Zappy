/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <memory>
    #include "window.hpp"
    #include "encapsulation/Raylibcpp.hpp"

typedef struct coord {
    float x;
    float y;
} coord_t;

class buttons {
    public:
        buttons(std::string string, coord_t coord, Color color, int size, GameEvent screen, const std::shared_ptr<Window> &ptr);
        ~buttons() = default;
        void update();
        void draw() {};
        void handleInput() {};
        void setCoord(coord_t coord) {_coord = coord;};
        coord_t getCoord() const {return _coord;};
        void setString(std::string string) {_string = string;};
        std::string getString() const {return _string;};
        void setColor(Color color) {_colorFont = color;};
        Color getColor() const {return _colorFont;};
        void setSize(int size) {_size = size;};
        int getSize() const {return _size;};
        void setScreen(GameEvent screen) {_screen = screen;};
        GameEvent getScreen() const {return _screen;};
        Rectangle getRectButton() const {return _rectButton;};
        Color getColorRect() const {return _colorRect;};
        bool getIsClicked() const {return _isClicked;};
        void setIsClicked(bool isClicked) {_isClicked = isClicked;};
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
