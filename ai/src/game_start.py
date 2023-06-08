import socket

from ai.src.player import Player, EnumObject, EnumHeader, EnumDirection
from ai.src.handle_packets import duplicate

def find_boss(player: Player):
    player.broadcast(EnumHeader.ASKBOSS.value + " Who\n", False)
    player.take(EnumObject.LINEMATE.value, False)
    player.take(EnumObject.FOOD.value, False)

    if player.boss != 0:
        player.boss = 1
        print("I AM THE BOSS\n")
    if (player.space == True):
        duplicate(player.args)
        player.space = False
        player.wait_broadcast()

def locate_boss(player: Player):

    while (player.pos_boss == -1):
        player.wait_broadcast()

    if (player.pos_boss == 0):
        player.broadcast(EnumHeader.IMHERE.value + " IMHERE\n")
        return True
    elif (player.pos_boss == 1 or player.pos_boss == 2 or player.pos_boss == 8):
        player.move()
        player.wait_broadcast()
        player.pos_boss = -1
    elif (player.pos_boss == 4 or player.pos_boss == 5 or player.pos_boss == 3):
        player.turn(EnumDirection.LEFT)
        player.wait_broadcast()
        player.pos_boss = -1
    elif (player.pos_boss == 6 or player.pos_boss == 7):
        player.turn(EnumDirection.RIGHT)
        player.wait_broadcast()
        player.pos_boss = -1
    return False

def join_boss(player: Player):
    if player.boss == 1:
        while (player.nbr_ai > 0):
            player.broadcast(EnumHeader.IMBOSS.value + " IMBOSS\n")
    else:
        while (locate_boss(player) == False):
            pass
