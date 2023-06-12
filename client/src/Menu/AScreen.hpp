/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** IScreen
*/

#ifndef ASCREEEN_HPP_
    #define ASCREEEN_HPP_

    #include "IScreen.hpp"

class AScreen : public IScreen {
    public:
        virtual ~AScreen() = default;
        void run(void) override;
        void draw(void) override;
        void createButtons(std::string string, coord coord, Color color, int size, GameEvent screen) override;
        void createText(std::string string, coord coord, Color color, int size);
        void drawButton(void) override;
        void drawText(void);
    private:
        virtual void handleInput(void) = 0;
    protected:
        Texture2D _background;
        std::vector<Button> _buttonsScreen;
        std::vector<Raylibcpp::RayText> _text;
        Raylibcpp::RayMusic _Raymusic;
        std::shared_ptr<Window> _window;
        Raylibcpp::RayWindow _rayWindow;
};

#endif /* !ASCREEEN_HPP_ */