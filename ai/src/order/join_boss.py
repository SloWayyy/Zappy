from ai.src.order.take_around import *

def init_join_boss(player):
    from ai.src.player import EnumOrder
    player.job = int(EnumOrder.JOIN_BOSS.value)

def locate_boss(player):
    from ai.src.player import EnumDirection, EnumHeader, EnumOrder
    from ai.src.priority_order.ping import ping
    from ai.src.order.square_collect import square_collect
    init_join_boss(player)
    while (player.pos_boss == -1):
        player.wait_broadcast()

    if (player.pos_boss == 0):
        print("je suis arrivé")
        ping(player)
        square_collect(player, 1)
        # player.broadcast(player.uuid + " " + EnumHeader.ANSWER.value + " " + player.boss_uuid + " " + EnumOrder.NOTHING.value, False)
        return True
    if (player.pos_boss == 1 or player.pos_boss == 2 or player.pos_boss == 8):
        player.move()
        print("je bouge")
        tmp, foot_case = look_item(player)
        for i in range (len(foot_case)):
            if (foot_case[i] != "player"):
                player.take(foot_case[i])
        player.wait_broadcast()
        player.pos_boss = -1
    elif (player.pos_boss == 4 or player.pos_boss == 5 or player.pos_boss == 3):
        print("pos: ", player.pos_boss)
        player.turn(EnumDirection.LEFT)
        print("je tourne left")
        player.wait_broadcast()
        player.pos_boss = -1
    elif (player.pos_boss == 6 or player.pos_boss == 7):
        print("pos: ", player.pos_boss)
        player.turn(EnumDirection.RIGHT)
        print("je tourne right")
        player.wait_broadcast()
        player.pos_boss = -1
    return False

def join_boss(player):
    while (locate_boss(player) == False):
        pass
