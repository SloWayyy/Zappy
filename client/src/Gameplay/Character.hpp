/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** character
*/

#ifndef CHARACTER_HPP_
    #define CHARACTER_HPP_

    #include <vector>
    #include "encapsulation/Raylibcpp.hpp"
    #include "Inventory.hpp"
    #include <memory>

enum Directions {
    RIGHT_DIR = 0,
    DOWN_DIR = -90,
    LEFT_DIR = 180,
    TOP_DIR = 90
};

enum Animations {
    SPAWN,
    DYING,
    WALKING,
    RIGHT_TURN,
    LEFT_TURN,
    NONE
};

class Character {
    public:
        Character() = default;
        Character(std::size_t animsCount, std::size_t animFrameCounter, Vector3 pos, std::size_t level, std::size_t orientation, std::string name, std::size_t id);
        ~Character() = default;
        Vector3 getPosition() const;
        Model getModel() const;
        void chooseAnimation(Animations anim);
        int getAnimFrameCounter() const;
        ModelAnimation *getAnimation(Animations anim) const;
        void setAnimFrameCounter(int animFrameCounter);
        Animations getCurrentlyAnimation() const;
        void setCurrentlyAnimation(Animations currentlyAnimation);
        void setPos(int x, int z, int orientation);
        void handleEvent();
        void run();
        void draw();
        size_t getLevel() const;
        std::string getTeamName() const;
        void setDirection(Directions direction);
        void setLevel(size_t level);
        Directions getDirection() const;
        std::size_t getId() const;
        std::shared_ptr<Inventory> getInventory() const;
    private:
        Model _model;
        std::vector<ModelAnimation *> _animations;
        Texture2D _texture;
        Vector3 _position;
        unsigned int _animsCount;
        int _animFrameCounter;
        Raylibcpp::RayModel _rayModel;
        Animations _currentlyAnimation;
        Directions _currentDirection;
        std::shared_ptr<Inventory> _inventory;
        std::size_t _level;
        std::size_t _id;
        std::string _teamname;
};

#endif /* !CHARACTER_HPP_ */
