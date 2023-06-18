from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.group_init import find_boss
from ai.src.player import ALL


def msg_create(sender: Player, receiver: str, header: str, order: str = None, data: str = "Nothing") -> str:
    if (order != None):
        return (sender.uuid + " " + header + " " + receiver + " " + order + " " + data)
    else:
        return (sender.uuid + " " + header + " " + receiver + " " + data)


def boss_routine(player: Player):
    for i in player.array_uuid:
        player.broadcast(msg_create(player, i["uuid"], EnumHeader.ORDER.value, EnumOrder.JOIN_BOSS.value), False)
        player.broadcast(msg_create(player, i["uuid"], EnumHeader.PRIORITY_ORDER.value, EnumPriorityOrder.PING.value), False)
    while True:
        player.broadcast(msg_create(player, ALL, EnumHeader.IMBOSS.value), False)

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
