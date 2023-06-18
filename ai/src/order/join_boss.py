from ai.src.order.take_around import *

def locate_boss(player):
    from ai.src.player import EnumDirection
    while (player.pos_boss == -1):
        player.wait_broadcast()

    if (player.pos_boss == 0):
        print("je suis arrivé")
        return True
    if (player.pos_boss == 1 or player.pos_boss == 2 or player.pos_boss == 8):
        player.move()
        tmp, foot_case = look_item(player)
        for i in range (len(foot_case)):
            if (foot_case[i] != "player"):
                player.take(foot_case[i])
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

def join_boss(player, _):
    while (locate_boss(player) == False):
        pass
