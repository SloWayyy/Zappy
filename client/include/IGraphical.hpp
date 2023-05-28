/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

    #include <memory>
    #include "encapsulation/Raylibcpp.hpp"

class IGraphical {
    public:
        virtual ~IGraphical() = default;
};

class Graphic : public IGraphical {
    public:
        Graphic() {}
        ~Graphic() = default;
    protected:
    private:
};


#endif /* !IGRAPHICAL_HPP_ */
