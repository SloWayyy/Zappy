cmake_minimum_required(VERSION 3.18)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(.)
include_directories(include)

add_executable(zappy_gui
        src/Main.cpp
        src/Core/Core.cpp
        src/Core/Window.cpp
        src/Gameplay/Gameplay.cpp
        src/Gameplay/Character.cpp
        src/Gameplay/Map.cpp
        src/Menu/Menu.cpp
        src/Menu/Tuto.cpp
        src/Menu/AScreen.cpp
        src/Menu/Button.cpp
        encapsulation/Cube.cpp
        encapsulation/Model.cpp
        encapsulation/Mouse.cpp
        encapsulation/Text.cpp
        encapsulation/Window.cpp
        )

target_link_libraries(zappy_gui raylib)
