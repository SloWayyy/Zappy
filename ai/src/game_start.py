import socket

from ai.src.player import Player, EnumObject, EnumHeader, EnumDirection
from ai.src.handle_packets import duplicate
from ai.src.players.routine_boss import look_item

def find_boss(player: Player):
    player.broadcast(EnumHeader.ASKBOSS.value + " Who\n", False)
    player.take(EnumObject.LINEMATE.value, False)
    player.take(EnumObject.FOOD.value, False)

    if player.boss != 0:
        player.boss = 1
        print("I AM THE BOSS\n")
        if (player.slot > 0):
            for _ in range(0, player.slot):
                duplicate(player.args)
                player.wait_broadcast()

def locate_boss(player: Player):

    while (player.pos_boss == -1):
        player.wait_broadcast()

    if (player.pos_boss == 0):
        player.broadcast(EnumHeader.IMHERE.value + " IMHERE\n")
        print("je suis arrivé")
        return True
    if (player.pos_boss == 1 or player.pos_boss == 2 or player.pos_boss == 8):
        player.move()
        tmp, foot_case = look_item(player)
        print("move")
        print("foot_case: ", foot_case, "tmp: ", tmp, "\n")
        for i in range (1, len(foot_case)):
            if (foot_case[i] != "player"):
                print("take : ",foot_case[i] , player.take(foot_case[i]))
        player.wait_broadcast()
        player.pos_boss = -1
    elif (player.pos_boss == 4 or player.pos_boss == 5 or player.pos_boss == 3):
        player.turn(EnumDirection.LEFT)
        print("turn left")
        player.wait_broadcast()
        player.pos_boss = -1
    elif (player.pos_boss == 6 or player.pos_boss == 7):
        player.turn(EnumDirection.RIGHT)
        print("turn right")
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
