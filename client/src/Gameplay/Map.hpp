/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Map.hpp
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <string>
    #include <iostream>
    #include <vector>
    #include <map>
    #include <unordered_map>
    #include "encapsulation/Raylibcpp.hpp"
    #include <array>

struct mapSize {
    std::size_t height;
    std::size_t width;
};

class Map {
    enum modelType {
        BANANA,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };
    public:
        Map() = default;
        Map(std::size_t height , std::size_t width);
        ~Map() = default;
        void drawMineral(modelType type, Vector3 position, float scale);
        void setHeight(std::size_t height);
        void setWidth(std::size_t width);
        std::size_t getheight() const;
        std::size_t getwidth() const;
        std::vector<std::string> &getMap();
        modelType getmodelBanana() const {return BANANA;};
        modelType getmodelLinemate() const {return LINEMATE;};
        modelType getmodelDeraumere() const {return DERAUMERE;};
        modelType getmodelSibur() const {return SIBUR;};
        modelType getmodelMendiane() const {return MENDIANE;};
        modelType getmodelPhiras() const {return PHIRAS;};
        modelType getmodelThystame() const {return THYSTAME;};
        Vector3 getcubePosition() const;
        void setcubePosition(Vector3 position);
        Model getmodel() const;
        Model getmodelPlatform() const;
        Model getmodelSkybox() const;
        void draw(Model model, Vector3 _position, float scale);
        void drawColor(Model model, Vector3 _position, float scale, Color color);
        Texture2D getLevel() const;
        Texture2D getTeam() const;
        void setNight();
        void setMorning();
        void run();
        std::map<std::pair<std::size_t, std::size_t>, std::array<int, 7>> &getMapInventory();
    private:
        Model _model;
        Texture2D _texture;
        Model _modelPlatform;
        Texture2D _texturePlatform;
        Model _modelSkybox;
        Texture2D _textureSkyboxMorning;
        Texture2D _textureSkyboxNight;
        std::vector<std::string> map;
        mapSize _mapSize;
        Vector3 _cubePosition;
        std::unordered_map<modelType, std::pair<Model, Texture2D>> _modelMap;
        std::vector<Vector3> _MineralPositionArray;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayCube _rayCube;
        Texture2D _level;
        Texture2D _team;
        std::map<std::pair<std::size_t, std::size_t>, std::array<int, 7>> _mapInventory;
};

#endif /* !MAP_HPP_ */