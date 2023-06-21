/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#ifndef GAMEPLAY_HPP_
    #define GAMEPLAY_HPP_

    #include <memory>
    #include <map>
    #include <vector>
    #include <chrono>
    #include "src/Gameplay/Map.hpp"
    #include "src/Core/Window.hpp"
    #include "src/Gameplay/Character.hpp"
    #include "src/Gameplay/Egg.hpp"
    #include "src/Gameplay/Display.hpp"
    #include "encapsulation/Raylibcpp.hpp"
    #include "ICommunicationModule.hpp"

enum CameraType {
    CAMERA_FIRST,
    CAMERA_SECOND,
    CAMERA_THIRD
};

class Gameplay {
    public:
        class Error : public std::exception {
            public:
                Error(std::string const &message) : _message(message) {};
                ~Error() = default;
                const char *what() const noexcept override { return _message.c_str(); }
            private:
                std::string _message;
        };
        Gameplay(std::shared_ptr<Window> _window);
        ~Gameplay();
        void run(void);
        void initPlayer(Vector3 pos, std::size_t level, std::size_t orientation, std::size_t id, std::string teamname, std::map<std::size_t, Texture2D> textures, std::vector<ModelAnimation *> animations);
        void initEgg(std::size_t id, float x, float y);
        void runPlayers(void);
        void runEggs(void);
        void handleInput(void);
        void drawMap(void);
        void drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color);
        bool setCurrentCharacter();
        void DisplayInformations();
        void setDisplayMode();
        void displayBroadcast();
        void setIsDisplay(bool isDisplay);
        void setCameraType(CameraType cameraType);
        CameraType getCameraType(void) const;
        std::shared_ptr<Map> getMap() const;
        std::map<std::size_t, Texture2D> getTextures() const;
        void setTextures();
        std::vector<ModelAnimation *> getAnimations() const;
        void setAnimations();
        std::map<std::size_t, std::shared_ptr<Character>> &getCharacters();
        std::map<std::size_t, std::shared_ptr<Egg>> &getEggs();
        void displayMinerals();
        Texture2D getTextureEgg() const;
        Model getModelEgg() const;
        void setTextureEgg();
        void setModelEgg();
        std::map<std::pair<std::size_t, std::size_t>, std::string> &getIncantation();
        void addIncantation(std::size_t x, std::size_t y, std::string string);
    private:
        std::shared_ptr<Window> _window;
        Display _display;
        std::shared_ptr<Map> _map;
        std::map<std::size_t, std::shared_ptr<Character>> _characters;
        std::map<std::size_t, std::shared_ptr<Egg>> _eggs;
        std::size_t _currentCharacterId;
        std::size_t _currentCharacterIndex;
        std::shared_ptr<Character> _currentCharacter;
        Raylibcpp::RayWindow _rayWindow;
        Raylibcpp::RayCube _rayCube;
        Raylibcpp::RayModel _rayModel;
        Raylibcpp::RayText _rayText;
        bool _isDisplay;
        CameraType _cameraType;
        std::map<std::size_t, Texture2D> _textures;
        Texture2D _textureEgg;
        Model _modelEgg;
        std::vector<ModelAnimation *> _animations;
        std::map<std::pair<std::size_t, std::size_t>, std::string> _incantation;
        std::chrono::steady_clock::time_point _startTime;
        std::chrono::steady_clock::time_point _currentTime;
        std::chrono::duration<double> _elapsedSeconds;
};

#endif /* !GAMEPLAY_HPP_ */
