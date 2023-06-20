from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.order.handle_incantation import handle_incantation
from ai.src.group_init import find_boss
from ai.src.player import ALL
from ai.src.order.level_up import level_up
from ai.src.order.take_around import take_around

def msg_create(sender: Player, receiver: str, header: str, order: str = None, data: str = "Nothing") -> str:
    if (order != None):
        return (sender.uuid + " " + header + " " + receiver + " " + order + " " + data)
    else:
        return (sender.uuid + " " + header + " " + receiver + " " + data)

def boss_routine(player: Player):
    # take_around(player, [])
    while True:
        for i in player.array_uuid:
            player.broadcast(msg_create(player, i["uuid"], EnumHeader.ORDER.value, EnumOrder.JOIN_BOSS.value))
    # while True:
    #     # for i in player.array_uuid:
    #     #     if str(i["pos"]) != EnumOrder.JOIN_BOSS.value:
    #             # print("I'm the boss")
    #     player.broadcast(msg_create(player, ALL, EnumHeader.IMBOSS.value))
    #     handle_incantation(player)

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
