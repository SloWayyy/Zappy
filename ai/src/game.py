from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.group_init import find_boss
from ai.src.player import ALL

def boss_routine(player: Player):
    for i in player.array_uuid:
        player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.JOIN_BOSS.value + " Nothing", False)
        player.broadcast(player.uuid + " " + EnumHeader.PRIORITY_ORDER.value + " " + i["uuid"] + " " + EnumPriorityOrder.PING.value + " Nothing", False)
    while True:
        player.broadcast(player.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " " + "JAJAJA", False)

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
