/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Main
*/

#include "raylib.h"
#include "character.hpp"
#include "encapsulation/Raylibcpp.hpp"
#include "core.hpp"
#include <memory>

int main(void)
{
    std::unique_ptr<Core> core = std::make_unique<Core>();
    core->run();
    return 0;
}
