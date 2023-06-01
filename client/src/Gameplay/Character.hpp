/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#ifndef CHARACTER_HPP_
    #define CHARACTER_HPP_

    #include "encapsulation/Raylibcpp.hpp"

class Character : public Raylibcpp::RayModel {
    public:
        Character() = default;
        Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos);
        ~Character() = default;
        Vector3 getPosition() const;
        void animation();
        void run();
        void draw();
    protected:
        Model _model;
        ModelAnimation *_anims;
        unsigned int _animsCount;
        int _animFrameCounter;
        Texture2D _texture;
        Vector3 _position;
        Raylibcpp::RayModel _rayModel;
    private:
};

#endif /* !CHARACTER_HPP_ */
