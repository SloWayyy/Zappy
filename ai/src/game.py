import os
import socket

from ai.src.player import Player, EnumObject, EnumHeader, EnumDirection
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
        player.wait_answer()

def locate(player: Player):
    print("boss pos {}\n".format(player.pos))
    if (player.pos == 0):
        player.pos = -1
        player.broadcast(EnumHeader.IMHERE.value + " IMHERE\n")
        print ("IMHERE\n")
        return True
    elif (player.pos == 1 or player.pos == 2 or player.pos == 8):
        player.pos = -1
        player.move()
        print("IMOVE\n")
    elif (player.pos == 4 or player.pos == 5 or player.pos == 3):
        player.pos = -1
        player.turn(EnumDirection.LEFT.value)
        print("LEFT\n")
    elif (player.pos == 6 or player.pos == 7):
        player.pos = -1
        player.turn(EnumDirection.RIGHT.value)
        print("RIGHT\n")

    return False

def join_boss(player: Player):
    print("join_boss {}\n".format(player.boss))
    if player.boss == 1:
        while (player.ai > 0):
            print("ai {}\n".format(player.ai))
            player.broadcast(EnumHeader.IMBOSS.value + " IMBOSS\n")
    elif player.boss == 0:
        while (player.positionned == False):
            player.positionned = locate(player)


def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    # print(player.pos)
    join_boss(player)


    # while True:
    #     player.look()
    sock.close()
