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
    list_tmp = []
    for i in list:
        list_tmp.append(i.split(" "))
    foot_case = list_tmp.pop(0)
    return list_tmp[:3], foot_case

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

    for _ in range(0, 3):
        player.turn(EnumDirection.RIGHT)
        for _ in range(0, 2):
            player.move()
            for j in list_item[counter]:
                if (j[0] != "V"):
                    player.take(j)
            counter += 1
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
        player.move()

def dump_item(player: Player):
    inventory = player.inventory()
    for i in range(1, len(inventory)):
        for _ in range(0, inventory[i]):
            if i == 1:
                player.set(EnumObject.LINEMATE)
            if i == 2:
                player.set(EnumObject.DERAUMERE)
            if i == 3:
                player.set(EnumObject.SIBUR)
            if i == 4:
                player.set(EnumObject.MENDIANE)
            if i == 5:
                player.set(EnumObject.PHIRAS)
            if i == 6:
                player.set(EnumObject.THYSTAME)

def routine_boss(player: Player):
    list_item = []
    player.take(EnumObject.FOOD.value)
    for i in range(0, 4):
        tmp, _ = look_item(player)
        for j in tmp:
            list_item.append(j)
        player.turn(EnumDirection.RIGHT)
    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2

    first_pattern(list_item, player)
    second_pattern(list_item[2:], player)
    player.take(EnumObject.FOOD.value)

def look_aroud_ai(player: Player):
    list_item = []
    for _ in range(0, 3):
        player.move()
    tmp, foot_case = look_item(player)
    for i in tmp:
        list_item.append(i)
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
    tmp, _ = look_item(player)
    for j in tmp:
        list_item.append(j)
    list_item.insert(0, list_item.pop())
    return list_item, foot_case

def get_item_ai(player: Player, list_item: list, foot_case: list):
    for i in foot_case:
        player.take(i)
    player.move()
    print("list: ", list_item.reverse())
    # for i in list_item.reverse():
    #     player.take(i)

def routine_ai(player: Player):
    list_item, foot_case = look_aroud_ai(player)
    get_item_ai(player, list_item, foot_case)

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    if player.boss == 1:
        routine_boss(player)
        print(player.inventory())
    else:
        routine_ai(player)
    sock.close()
