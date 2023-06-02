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

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)


    find_boss(player)


    while True:
        player.look()
    sock.close()
