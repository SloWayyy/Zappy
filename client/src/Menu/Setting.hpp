/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setting
*/

#ifndef SETTING_HPP_
    #define SETTING_HPP_

    #include "AScreen.hpp"

class Setting : public AScreen {
    public:
        Setting(std::shared_ptr<Window> window);
        ~Setting() = default;
    private:    
        void handleInput() override;
        size_t _volume;
        size_t _fps;
        Raylibcpp::RayMouse _rayMouse;
};

#endif /* !SETTING_HPP_ */