
from ai.src.order.take_around import look_item

def init_join_boss(player):
    from ai.src.player import EnumOrder
    player.job = int(EnumOrder.JOIN_BOSS.value)

def locate_boss(player):
    from ai.src.player import EnumDirection
    init_join_boss(player)
    while (player.pos_boss == -1):
        player.wait_broadcast()

    if (player.pos_boss == 0):
        print(player.boss_uuid + " is the boss\n")
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

def join_boss(player):
    while (locate_boss(player) == False):
        pass
