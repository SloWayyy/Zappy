/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** inventory.hpp
*/

#ifndef INVENTORY_HPP_
    #define INVENTORY_HPP_

    #include <cstddef>

class Inventory {
    public:
        Inventory();
        ~Inventory() = default;
        void setFood(std::size_t food);
        void setLinemate(std::size_t linemate);
        void setDeraumere(std::size_t deraumere);
        void setSibur(std::size_t sibur);
        void setMendiane(std::size_t mendiane);
        void setPhiras(std::size_t phiras);
        void setThystame(std::size_t thystame);
        std::size_t getFood() const;
        std::size_t getLinemate() const;
        std::size_t getDeraumere() const;
        std::size_t getSibur() const;
        std::size_t getMendiane() const;
        std::size_t getPhiras() const;
        std::size_t getThystame() const;
    private:
        std::size_t _food;
        std::size_t _linemate;
        std::size_t _deraumere;
        std::size_t _sibur;
        std::size_t _mendiane;
        std::size_t _phiras;
        std::size_t _thystame;
};

#endif /* !INVENTORY_HPP_ */
