/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#ifndef CHARACTER_HPP_
    #define CHARACTER_HPP_

    #include "encapsulation/Raylibcpp.hpp"

class character : public Raylibcpp::RayModel {
    public:
        character() = default;
        character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos);
        ~character() = default;
        void animation();
        void run();
        void draw();
        void handleInput();
    protected:
        Model _model;
        ModelAnimation *_anims;
        unsigned int _animsCount;
        int _animFrameCounter;
        Texture2D _texture;
        Vector3 _position;
    private:
};

#endif /* !CHARACTER_HPP_ */
