import socket
import re

from ai.src.game_start import find_boss, join_boss
from ai.src.player import Player, EnumObject, EnumHeader, EnumDirection

def look_item(player : Player):
    str: str = player.look()
    print("apres look ", str)
    str = str.replace("[ ", "")
    str = str.replace(", ]", ", V,")
    str = str.replace(" ]", "")
    for i in range(0, 10):
        str = str.replace(",,", ", V,")
    # re.sub(",,", " , V ,", str)

    # re.sub("[ ", "", str)
    # re.sub(" ]", "", str)
    print("apres remove ", str)
    list : list = str.split(", ")
    list.pop(0)
    list_tmp = []
    print(list)
    print("\n")
    for i in list:
        list_tmp.append(i.split(" "))
    print(list_tmp)
    print("\n")
    return list_tmp[:3]

def routine_boss(player: Player):
    list_item = []
    for i in range(0, 4):
        tmp = look_item(player)
        # print(tmp)
        for j in tmp:
            list_item.append(j)
        player.turn(EnumDirection.RIGHT)
    print("\n\n")
    o = 0
    for i in list_item:
        o+=1
        print("{} : {}".format(o, i))
    print("\n")
    print("\n")

    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2
    k = 0
    for i in list_item:
        k+=1
        print("{} : {}".format(k, i))

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
