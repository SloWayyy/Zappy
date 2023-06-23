from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.order.manage_order import manage_order
from ai.src.group_init import find_boss
from ai.src.player import ALL
from ai.src.order.level_up import level_up
from ai.src.order.take_around import take_around

def msg_create(sender: Player, receiver: str, header: str, order: str = None, data: str = "Nothing") -> str:
    if (order != None):
        return (sender.uuid + " " + header + " " + receiver + " " + order + " " + data)
    else:
        return (sender.uuid + " " + header + " " + receiver + " " + data)

def boss_routine(boss: Player):
    for i in boss.array_uuid:
        boss.broadcast(msg_create(boss, i["uuid"], EnumHeader.ORDER.value, EnumOrder.JOIN_BOSS.value))
    take_around(boss, 4)
    while True:
        boss.broadcast(msg_create(boss, ALL, EnumHeader.IMBOSS.value))
        manage_order(boss)

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
