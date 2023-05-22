cmake_minimum_required(VERSION 3.18)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

include_directories(.)

add_executable(zappy_gui
        src/Main.cpp
        )

target_link_libraries(zappy_gui OgreBites)
