/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gameplay
*/

#include "src/Gameplay/Gameplay.hpp"

Gameplay::Gameplay(std::shared_ptr<Window> _window) : _window(_window), _currentCharacterId(0), _currentCharacterIndex(0)
{
    this->_isDisplay = true;
    this->_display = Display(this->_window);
    this->_cameraType = CAMERA_THIRD;
    this->setTextures();
    this->setAnimations();
    this->_map = std::make_shared<Map>(10, 10);
}

Gameplay::~Gameplay()
{
    for (auto &textures : this->_textures) {
        try {
            this->_rayModel.unloadTexture(textures.second);
        } catch (const Raylibcpp::Error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    for (auto &animations : this->_animations) {
        try {
            this->_rayModel.unloadModelAnimations(animations, 0);
        } catch (const Raylibcpp::Error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Gameplay::setTextures()
{
    try {
        this->_textures.insert(std::pair<std::size_t, Texture2D>(1, this->_rayModel.loadTexture("client/assets/monster/textures/monsterBLUE.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(2, this->_rayModel.loadTexture("client/assets/monster/textures/monsterGREEN.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(3, this->_rayModel.loadTexture("client/assets/monster/textures/monsterRED.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(4, this->_rayModel.loadTexture("client/assets/monster/textures/monsterPINK.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(5, this->_rayModel.loadTexture("client/assets/monster/textures/monsterORANGE.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(6, this->_rayModel.loadTexture("client/assets/monster/textures/monsterBLACK.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(7, this->_rayModel.loadTexture("client/assets/monster/textures/monsterGOLD.png")));
        this->_textures.insert(std::pair<std::size_t, Texture2D>(8, this->_rayModel.loadTexture("client/assets/monster/textures/monsterWHITE.png")));
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Gameplay constructor failed");
    }
}

std::map<std::size_t, Texture2D> Gameplay::getTextures() const
{
    return this->_textures;
}

void Gameplay::setAnimations()
{
    unsigned int animCount = 0;

    try {
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterSpawn.iqm", &animCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterDying.iqm", &animCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterWalking.iqm", &animCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterRightTurn.iqm", &animCount));
        this->_animations.push_back(this->_rayModel.loadModelAnimations("client/assets/monster/animations/monsterLeftTurn.iqm", &animCount));
    } catch (const Raylibcpp::Error &e) {
        std::cerr << e.what() << std::endl;
        throw Error("Error: Gameplay constructor failed");
    }
}

std::vector<ModelAnimation *> Gameplay::getAnimations() const
{
    return this->_animations;
}

void Gameplay::initPlayer(Vector3 pos, std::size_t level, std::size_t orientation, std::size_t id, std::string teamname, std::map<std::size_t, Texture2D> textures, std::vector<ModelAnimation *> animations)
{
    std::shared_ptr<Character> player = std::make_shared<Character>(5, 0, pos, level, orientation, teamname, id, textures, animations);

    this->_characters.insert(std::pair<std::size_t, std::shared_ptr<Character>>(id, player));
    this->_characters[id]->setCurrentlyAnimation(SPAWN);
}

void Gameplay::initEgg(std::size_t id, float x, float y)
{
    std::shared_ptr<Egg> egg = std::make_shared<Egg>(id, x, y);

    this->_eggs.insert(std::pair<std::size_t, std::shared_ptr<Egg>>(id, egg));
}

void Gameplay::runPlayers(void)
{
    for (auto &character : this->_characters) {
        character.second->run();
    }
}

void Gameplay::runEggs(void)
{
    for (auto &egg : this->_eggs) {
        egg.second->run();
    }
}

void Gameplay::drawTextOnScreen(std::string text, int fontSize, int posX, int posY, Color color)
{
    this->_rayWindow.endMode3D();
    this->_rayText.drawText(text, posX, posY, fontSize, color);
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Gameplay::displayBroadcast()
{
    this->_rayWindow.endMode3D();
    for (auto &character : this->_characters) {
        if (character.second->getBroadMessage().empty() == false) {
            this->_rayModel.drawRectangle(0, this->_window->getScreenWidth() - 80, 1350, 30, {130, 130, 130, 255});
            this->_rayText.drawText(character.second->getBroadMessage(), 10, this->_window->getScreenWidth() - 75, 10, BLACK);
        }
    }
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Gameplay::run(void)
{
    this->drawMap();
    this->setDisplayMode();
    if (!this->_isDisplay) {
        this->drawTextOnScreen(this->_window->keyToString(this->_window->getKeyCam1()) + " : Camera 1", 20, this->_window->getScreenHeight() - 150, 10, BLACK);
        this->drawTextOnScreen(this->_window->keyToString(this->_window->getKeyCam2()) + " : Camera 2", 20, this->_window->getScreenHeight() - 150, 60, BLACK);
        this->drawTextOnScreen(this->_window->keyToString(this->_window->getKeyCam3()) + " : Camera 3", 20, this->_window->getScreenHeight() - 150, 110, BLACK);
        this->handleInput();
    }
    this->runPlayers();
    this->runEggs();
    this->displayBroadcast();
    if ((this->_cameraType == CAMERA_FIRST || this->_cameraType == CAMERA_SECOND) && this->_isDisplay == false)
        this->DisplayInformations();
    if (this->_isDisplay) {
        this->_window->setDefaultCamera();
        this->_display.run(std::map<std::size_t, std::shared_ptr<Character>>(this->_characters), _map);
    }
}

bool Gameplay::setCurrentCharacter()
{
    bool isSet = false;
    std::size_t i = 0;
    std::size_t size = this->_characters.size();
    int index = -1;

    for (auto &character : this->_characters)
        if (character.first == this->_currentCharacterIndex)
            index = i;
    if (size == 0)
        return false;
    if (index == -1) {
        for (auto &character : this->_characters) {
            this->_currentCharacter = character.second;
            this->_currentCharacterIndex = character.first;
            return true;
        }
    }
    for (auto &character : this->_characters) {
        if (isSet == true) {
            this->_currentCharacter = character.second;
            this->_currentCharacterIndex = character.first;
            return true;
        }
        if (character.first == this->_currentCharacterIndex)
            isSet = true;
    }
    this->_currentCharacterIndex = _characters.begin()->first;
    this->_currentCharacter = _characters.begin()->second;
    return true;
}

void Gameplay::DisplayInformations(void)
{
    std::size_t height = this->_window->getScreenHeight();
    std::size_t width = this->_window->getScreenWidth();
    std::string id = "ID " + std::to_string(this->_currentCharacter->getId());
    std::string level = "Level: " + std::to_string(this->_currentCharacter->getLevel());
    std::string food = "Food: " + std::to_string(this->_currentCharacter->getInventory()->getFood());
    std::string linemate = "Linemate: " + std::to_string(this->_currentCharacter->getInventory()->getLinemate());
    std::string deraumere = "Deraumere: " + std::to_string(this->_currentCharacter->getInventory()->getDeraumere());
    std::string sibur = "Sibur: " + std::to_string(this->_currentCharacter->getInventory()->getSibur());
    std::string mendiane = "Mendiane: " + std::to_string(this->_currentCharacter->getInventory()->getMendiane());
    std::string phiras = "Phiras: " + std::to_string(this->_currentCharacter->getInventory()->getPhiras());
    std::string thystame = "Thystame: " + std::to_string(this->_currentCharacter->getInventory()->getThystame());

    this->_rayWindow.endMode3D();
    this->_rayModel.drawRectangle(height - (height / 4), width / 3, height / 4, width / 1.5, {130, 130, 130, 200});
    this->_rayModel.drawTextureEx(this->_map->getLevel(), {height - 450.0f, (width / 3) + 80.0f}, 0.0f, 0.2f, WHITE);
    this->_rayModel.drawTextureEx(this->_map->getTeam(), {height - 440.0f, (width / 3) + 200.0f}, 0.0f, 0.2f, WHITE);
    this->_rayText.drawText(id, height - 300, (width / 3) + 20, 80, RED);
    this->_rayText.drawText(level, height - 320, (width / 3) + 150, 30, BLACK);
    this->_rayText.drawText(this->_currentCharacter->getTeamName(), height - 320, (width / 3) + 230, 30, BLACK);
    this->_rayText.drawText(food, height - 300, (width / 3) + 300, 30, BLACK);
    this->_rayText.drawText(linemate, height - 450, (width / 3) + 350, 30, BLACK);
    this->_rayText.drawText(deraumere, height - 220, (width / 3) + 350, 30, BLACK);
    this->_rayText.drawText(sibur, height - 450, (width / 3) + 400, 30, BLACK);
    this->_rayText.drawText(mendiane, height - 220, (width / 3) + 400, 30, BLACK);
    this->_rayText.drawText(phiras, height - 450, (width / 3) + 450, 30, BLACK);
    this->_rayText.drawText(thystame, height - 220, (width / 3) + 450, 30, BLACK);
    this->_rayWindow.beginMode3D(this->_window->getCamera());
}

void Gameplay::setDisplayMode(void)
{
    if (this->_rayWindow.isKeyReleased(KEY_TAB)) {
        if (this->_isDisplay == false) {
            this->setCameraType(CAMERA_THIRD);
            this->_isDisplay = true;
        }
        else if (this->_isDisplay == true) {
            this->_isDisplay = false;
        }
    }
}

void Gameplay::handleInput(void)
{
    if (this->_rayWindow.isKeyDown(KEY_ESCAPE) || _rayWindow.windowShouldClose())
        this->_window->setExit(true);
    if (this->_rayWindow.isKeyReleased(this->_window->getKeyCam1())) {
        if (!_characters.empty()) {
            if (this->setCurrentCharacter() == false)
                return;
            this->_window->setCamera({_currentCharacter->getPosition().x, _currentCharacter->getPosition().y + 2.0f, _currentCharacter->getPosition().z - 0.5f}, { 10.0f, 2.0f, 10.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
            this->setCameraType(CAMERA_FIRST);
        }
    }
    if (this->_rayWindow.isKeyReleased(this->_window->getKeyCam2())) {
        if (!_characters.empty()) {
            if (this->setCurrentCharacter() == false)
                return;
            this->_window->setCamera({_currentCharacter->getPosition().x, _currentCharacter->getPosition().y + 4.0f, _currentCharacter->getPosition().z - 4.0f}, { 0.6f, -4.5f, 60.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
            this->setCameraType(CAMERA_SECOND);
        }
    }
    if (this->_rayWindow.isKeyReleased(this->_window->getKeyCam3())) {
        this->_window->setDefaultCamera();
        this->setCameraType(CAMERA_THIRD);
    }
}

void Gameplay::drawMap(void)
{
    float _x = 0.0f;
    float _y = 0.0f;
    std::size_t height = this->_map->getheight();
    std::size_t width = this->_map->getwidth();
    std::size_t tileX = this->_display.getTileX();
    std::size_t tileY = this->_display.getTileY();

    if (this->_window->getIsChanged() == true) {
        this->_window->setIsChanged(false);
        if (this->_window->getIsNight() == true)
            this->_map->setNight();
        else
            this->_map->setMorning();
    }
    this->_map->draw(this->_map->getmodelSkybox(), {60.0f, -0.5f, 60.0f}, 500.0f);
    for (std::size_t y = 0; y < height; y++) {
        for (std::size_t x = 0; x < width; x++) {
            this->_map->setcubePosition({ _x, -0.45f, _y });
            this->_map->draw(this->_map->getmodel(), this->_map->getcubePosition(), 2.0f);
            this->_map->draw(this->_map->getmodelPlatform(), {this->_map->getcubePosition().x, this->_map->getcubePosition().y + 1.6f, this->_map->getcubePosition().z}, 0.02f);
            _x += 4.0f;
            for (auto &incantation : this->_incantation) {
                if (incantation.first.first == x && incantation.first.second == y) {
                    this->_rayCube.drawCube({this->_map->getcubePosition().x, this->_map->getcubePosition().y + 1.5f, this->_map->getcubePosition().z}, 4.0f, 0.6f, 4.0f, RED);
                }
            }
            if (this->_isDisplay == true && (tileX == x && tileY == y))
                this->_rayCube.drawCube({this->_map->getcubePosition().x, this->_map->getcubePosition().y + 1.5f, this->_map->getcubePosition().z}, 4.0f, 0.6f, 4.0f, {255, 255, 255, 200});
        }
        _x = 0.0f;
        _y += 4.0f;
    }
    for (auto &tile : this->_map->getMapInventory()) {
        if (tile.second[0] > 0)
            this->_map->drawMineral(this->_map->getmodelFood(), {tile.first.first * 4.0f, 1.38f, tile.first.second * 4.0f}, 0.04f);
        if (tile.second[1] > 0)
            this->_map->drawMineral(this->_map->getmodelLinemate(), {tile.first.first * 4.0f - 1.0f, 1.38f, tile.first.second * 4.0f - 1.0f}, 0.2f);
        if (tile.second[2] > 0)
            this->_map->drawMineral(this->_map->getmodelDeraumere(), {tile.first.first * 4.0f, 1.38f, tile.first.second * 4.0f - 1.0f}, 0.2f);
        if (tile.second[3] > 0)
            this->_map->drawMineral(this->_map->getmodelSibur(), {tile.first.first * 4.0f + 1.0f, 1.38f, tile.first.second * 4.0f - 1.0f}, 0.2f);
        if (tile.second[4] > 0)
            this->_map->drawMineral(this->_map->getmodelMendiane(), {tile.first.first * 4.0f - 1.0f, 1.38f, tile.first.second * 4.0f}, 0.2f);
        if (tile.second[5] > 0)
            this->_map->drawMineral(this->_map->getmodelPhiras(), {tile.first.first * 4.0f + 1.0f, 1.38f, tile.first.second * 4.0f}, 0.2f);
        if (tile.second[6] > 0)
            this->_map->drawMineral(this->_map->getmodelThystame(), {tile.first.first * 4.0f, 1.38f, tile.first.second * 4.0f + 1.0f}, 0.2f);
    }
}

void Gameplay::setIsDisplay(bool isDisplay)
{
    this->_isDisplay = isDisplay;
}

void Gameplay::setCameraType(CameraType camera)
{
    this->_cameraType = camera;
}

CameraType Gameplay::getCameraType(void) const
{
    return (this->_cameraType);
}

std::shared_ptr<Map> Gameplay::getMap() const
{
    return this->_map;
}

std::map<std::size_t, std::shared_ptr<Character>> &Gameplay::getCharacters()
{
    return this->_characters;
}

std::map<std::size_t, std::shared_ptr<Egg>> &Gameplay::getEggs()
{
    return this->_eggs;
}

std::map<std::pair<std::size_t, std::size_t>, std::string> &Gameplay::getIncantation()
{
    return this->_incantation;
}

void Gameplay::addIncantation(std::size_t x, std::size_t y, std::string string)
{
    this->_incantation.insert({{x, y}, string});
}