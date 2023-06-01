/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#ifndef CHARACTER_HPP_
    #define CHARACTER_HPP_

    #include "encapsulation/Raylibcpp.hpp"

class Character {
    public:
        Character() = default;
        Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos);
        ~Character() = default;
        Vector3 getPosition() const;
        void animation();
        void run();
        void draw();
    private:
        Model _model;
        ModelAnimation *_anims;
        Texture2D _texture;
        Vector3 _position;
        unsigned int _animsCount;
        int _animFrameCounter;
        Raylibcpp::RayModel _rayModel;
};

#endif /* !CHARACTER_HPP_ */
