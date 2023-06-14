/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Egg.hpp
*/

#ifndef EGG_HPP_
    #define EGG_HPP_

    #include <memory>
    #include "encapsulation/Raylibcpp.hpp"

class Egg {
    public:
        Egg(std::size_t id, float x, float y);
        ~Egg() = default;
        std::size_t getId() const;
        Vector3 getPosition() const;
        void run(void);
    private:
        Model _model;
        Texture2D _texture;
        Raylibcpp::RayModel _rayModel;
        std::size_t _id;
        Vector3 _position;
};

#endif /* !EGG_HPP_ */