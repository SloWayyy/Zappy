cmake_minimum_required(VERSION 3.18)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(.)
include_directories(include)

add_executable(zappy_gui
        src/Main.cpp
        src/character.cpp
        src/Map.cpp
        src/window.cpp
        src/core.cpp
        encapsulation/draw.cpp
        encapsulation/model.cpp
        Menu/src/menu.cpp
        )

target_link_libraries(zappy_gui raylib)
