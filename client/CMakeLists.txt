cmake_minimum_required(VERSION 3.18)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ldl -g3")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(.)
include_directories(include)
include_directories(libs/include)

add_executable(zappy_gui
        src/Main.cpp
        src/Core/Core.cpp
        src/Core/Window.cpp
        src/Gameplay/Gameplay.cpp
        src/Gameplay/Character.cpp
        src/Gameplay/Egg.cpp
        src/Gameplay/Display.cpp
        src/Gameplay/Inventory.cpp
        src/Gameplay/Map.cpp
        src/Menu/Menu.cpp
        src/Menu/Tuto.cpp
        src/Menu/Gameover.cpp
        src/Menu/Setting.cpp
        src/Menu/AScreen.cpp
        src/Menu/Button.cpp
        src/Menu/Disconnect.cpp
        src/Menu/Credits.cpp
        src/Parser/Parser.cpp
        encapsulation/Cube.cpp
        encapsulation/Model.cpp
        encapsulation/Mouse.cpp
        encapsulation/Text.cpp
        encapsulation/Window.cpp
        encapsulation/Music.cpp
        encapsulation/Clock.cpp
        encapsulation/Sound.cpp
        )

target_link_libraries(zappy_gui raylib)
