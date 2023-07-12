/*
** EPITECH PROJECT, 2023
** server
** File description:
** constants.h
*/

#ifndef CONSTANTS_H_
    #define CONSTANTS_H_

    #define SUCCESS 0
    #define FAILURE 84

    #define DEFAULT_PORT 4242
    #define DEFAULT_WIDTH 10
    #define DEFAULT_HEIGHT 10
    #define DEFAULT_CLIENTS 4
    #define DEFAULT_FREQ 100
    #define DEFAULT_TEAM_SIZE sizeof(DEFAULT_TEAM_NAMES) / sizeof(char *)

    #define MAX_CONNECTIONS 1024
    #define MAX_PORT 65536
    #define MAX_WIDTH 100
    #define MAX_HEIGHT 100
    #define MAX_FREQ 10000
    #define MAX_TEAMS 100
    #define MAX_TEAM_SIZE 100
    #define BUFFER_SIZE 2048
    #define BUFFER_EXTRA 512
    #define BUFFER_MAX 65536

    #define MICROS_PER_SEC 1000000

    #define LINE_BREAK "\n"
    #define WELCOME_MESSAGE "WELCOME"
    #define DEBUG_PREFIX "[Debug] "
    #define GRAPHICAL_IDENTIFIER "GRAPHIC"

    #define REFILL_DELAY 20
    #define REFILL_COEFFICIENT 100
    #define FOOD_CONSUME_TICKS 126
    #define FOOD_DEFAULT 10
    #define MAX_ACTIONS 10
    #define VICTORY_LEVEL 8
    #define VICTORY_PLAYERS 6

    #define GRAPHICAL_MAP_SIZE "msz"
    #define GRAPHICAL_TILE_CONTENT "bct"
    #define GRAPHICAL_ALL_TILE_CONTENT "mct"
    #define GRAPHICAL_TEAMS_NAMES "tna"
    #define GRAPHICAL_PLAYER_POSITION "ppo"
    #define GRAPHICAL_PLAYER_LEVEL "plv"
    #define GRAPHICAL_PLAYER_INVENTORY "pin"
    #define GRAPHICAL_FREQUENCY "sgt"
    #define GRAPHICAL_CHANGE_FREQ "sst"

    #define GRAPHICAL_PLAYER_JOIN "pnw"
    #define GRAPHICAL_PLAYER_DEATH "pdi"
    #define GRAPHICAL_PLAYER_BROADCAST "pbc"
    #define GRAPHICAL_PLAYER_FORK "pfk"
    #define GRAPHICAL_PLAYER_EJECT "pex"
    #define GRAPHICAL_PLAYER_EGG "enw"
    #define GRAPHICAL_PLAYER_EGG_JOIN "ebo"
    #define GRAPHICAL_PLAYER_EGG_DEATH "edi"
    #define GRAPHICAL_PLAYER_TAKE "pgt"
    #define GRAPHICAL_PLAYER_SET "pdr"
    #define GRAPHICAL_PLAYER_INCANTATION_START "pic"
    #define GRAPHICAL_PLAYER_INCANTATION_END "pie"

    #define GRAPHICAL_CUSTOM "smg"
    #define GRAPHICAL_CUSTOM_EGG "eni"
    #define GRAPHICAL_CUSTOM_PAUSE "pse"

    #define GRAPHICAL_VICTORY "seg"
    #define GRAPHICAL_UNKNOWN "suc"
    #define GRAPHICAL_COMMAND_PARAMETER "sbp"

    #define FORWARD_DELAY 7
    #define LEFT_DELAY 7
    #define RIGHT_DELAY 7
    #define LOOK_DELAY 7
    #define INVENTORY_DELAY 1
    #define BROADCAST_DELAY 7
    #define SLOTS_DELAY 0
    #define FORK_DELAY 42
    #define EJECT_DELAY 7
    #define TAKE_DELAY 7
    #define SET_DELAY 7
    #define INCANTATION_DELAY 300

    #define PLAYER_MOVE_FORWARD "Forward"
    #define PLAYER_MOVE_LEFT "Left"
    #define PLAYER_MOVE_RIGHT "Right"
    #define PLAYER_LOOK "Look"
    #define PLAYER_INVENTORY "Inventory"
    #define PLAYER_BROADCAST "Broadcast"
    #define PLAYER_FORK "Fork"
    #define PLAYER_EJECT "Eject"
    #define PLAYER_UNUSED_SLOTS "Connect_nbr"
    #define PLAYER_TAKE_OBJECT "Take"
    #define PLAYER_SET_OBJECT "Set"
    #define PLAYER_INCANTATION "Incantation"

    #define PLAYER_OK "ok"
    #define PLAYER_KO "ko"
    #define PLAYER_EJECTION "eject:"
    #define PLAYER_MESSAGE "message"
    #define PLAYER_ELEVATION_START "Elevation underway"
    #define PLAYER_ELEVATION_END "Current level:"
    #define PLAYER_DEATH "dead"
    #define PLAYER_UNKNOWN PLAYER_KO

    #define UNUSED __attribute__((unused))

static const char * const DEFAULT_TEAM_NAMES[] = {
        "Team1",
        "Team2",
        "Team3",
        "Team4",
};

#endif
