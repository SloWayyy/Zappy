import socket
import re

from ai.src.game_start import find_boss, join_boss
from ai.src.player import Player, EnumObject, EnumHeader, EnumDirection

def look_item(player : Player):
    str: str = player.look()
    str = str.replace("[ ", "")
    str = str.replace(", ]", ", V,")
    str = str.replace(" ]", "")
    for i in range(0, 10):
        str = str.replace(",,", ", V,")
    list : list = str.split(", ")
    list.pop(0)
    list_tmp = []
    for i in list:
        list_tmp.append(i.split(" "))
    return list_tmp[:3]

def first_pattern(list_item : list, player: Player):
    player.move()
    if (list_item == []):
        return
    for i in list_item[0]:
        if (i[0] != "V"):
            player.take(i)
    player.turn(EnumDirection.RIGHT)
    player.move()
    for i in list_item[1]:
        player.take(i)

def second_pattern(list_item : list, player: Player):
    counter = 0

    for i in range(0, 3):
        player.turn(EnumDirection.RIGHT)
        for _ in range(0, 2):
            player.move()
            for j in list_item[counter]:
                if (j[0] != "V"):
                    player.take(j)
            counter += 1

def routine_boss(player: Player):
    list_item = []
    for i in range(0, 4):
        tmp = look_item(player)
        for j in tmp:
            list_item.append(j)
        player.turn(EnumDirection.RIGHT)
    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2

    first_pattern(list_item, player)
    second_pattern(list_item[2:], player)

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    if player.boss == 1:
        routine_boss(player)
        print(player.inventory())
    sock.close()
