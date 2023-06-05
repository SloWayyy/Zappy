import socket

from ai.src.game_start import find_boss, join_boss
from ai.src.player import Player, EnumObject, EnumHeader, EnumDirection

def look_item(player : Player):
    str: str = player.look()
    print(str)
    str = str.replace("[ ", "")
    str = str.replace(" ]", "")
    str = str.replace(",,", ", ,")
    print(str)
    list : list = str.split(", ")
    list.pop(0)
    list_tmp = []
    print(list)
    for i in list:
        list_tmp.append(i.split(" "))
    print(list_tmp)
    print("\n")
    return list_tmp

def routine_boss(player: Player):
    list_item = []
    for i in range(0, 4):
        tmp = look_item(player)
        for j in tmp:
            list_item.append(j)
        player.turn(EnumDirection.RIGHT)
    print("\n\n")
    for i in list_item:
        print(i)
    print("\n")
    print("\n")

    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2
    for i in list_item:
        print(i)

    while (1):
        pass

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    # while (1):
    if player.boss == 1:
        routine_boss(player)
        # else:
            # pass
    sock.close()
