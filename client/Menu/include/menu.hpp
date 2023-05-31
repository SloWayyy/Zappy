/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <memory>
    #include <vector>
    #include "encapsulation/Raylibcpp.hpp"
    #include "window.hpp"

typedef struct coord {
    float x;
    float y;
} coord_t;

class buttons : public Window {
    public:
        buttons(std::string string, coord_t coord, int nbButton, Color color, int size, GameEvent screen);
        ~buttons() = default;
        void update();
        void draw() {};
        void handleInput() {};
        void setCoord(coord_t coord) {_coord = coord;};
        coord_t getCoord() const {return _coord;};
        void setString(std::string string) {_string = string;};
        std::string getString() const {return _string;};
        void setColor(Color color) {_color = color;};
        Color getColor() const {return _color;};
        void setSize(int size) {_size = size;};
        int getSize() const {return _size;};
        void setNbButton(int nbButton) {_nbButton = nbButton;};
        int getNbButton() const {return _nbButton;};
        void setScreen(GameEvent screen) {_screen = screen;};
        GameEvent getScreen() const {return _screen;};
        Rectangle getRectButton() const {return _rectButton;};
        Color getColorRect() const {return _colorRect;};
        bool getIsClicked() const {return _isClicked;};
        void setIsClicked(bool isClicked) {_isClicked = isClicked;};
    private:
        coord_t _coord;
        std::string _string;
        Color _color;
        int _size;
        int _nbButton;
        bool _isClicked;
        GameEvent _screen;
        Rectangle _rectButton;
        Rectangle _btnBounds;
        Color _colorRect;
        Color _saveColorRect;
        Rectangle _mouse;
};

class Menu : public Raylibcpp::Draw, public Window {
    public:
        Menu();
        ~Menu() = default;
        void drawButton();
        void createButtons(std::string string, coord_t coord, Color color, int size, GameEvent screen);
        void init();
        void run();
        void stop();
        void draw();
        void handleInput();
    private:
        Texture2D _background;
        Raylibcpp::Text _text;
        std::vector<buttons> _buttonsScreen;
        int nbButton = 0;
};

#endif /* !MENU_HPP_ */
