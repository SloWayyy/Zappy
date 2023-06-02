import os
import socket

from ai.src.player import Player, EnumObject, EnumHeader
from ai.src.handle_packets import duplicate

def find_boss(player: Player):
    player.broadcast(EnumHeader.ASKBOSS.value + " Who\n")
    player.look()
    player.take(EnumObject.FOOD.value)

    if player.boss == 0:
        print("already a boss\n")
    else:
        player.boss = 1
        print("I'm the new boss\n")
    if (player.space == True):
        duplicate(player.args)
        player.space = False

def locate(player: Player):
    if (player.pos == -1):
        return False
    if (player.pos == 0):
        player.broadcast(EnumHeader.IMHERE.value + " IMHERE\n")
        return True
    if (player.pos == 1):
        player.move()
        return False
    

def join_boss(player: Player):
    if player.boss == 1:
        while (player.ia > 0):
            player.broadcast(EnumHeader.IMBOSS.value + " IMBOSS\n")
    if player.boss == 0:
        while (player.positionned == False):
            player.positionned = locate(player)


def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    # find_boss(player)
    # join_boss(player)
    print(player.look())

    while True:
        player.look()
    sock.close()
