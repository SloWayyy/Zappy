from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.group_init import find_boss
from ai.src.player import ALL

def boss_routine(player: Player):
    for i in player.array_uuid:
        player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.JOIN_BOSS.value, False)
        player.broadcast(player.uuid + " " + EnumHeader.PRIORITY_ORDER.value + " " + i["uuid"] + " " + EnumPriorityOrder.PING.value , False)
    while True:
        player.broadcast(player.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " " + "JAJAJA", False)
                # faire la routine boss ? mais si tout le monde n'est pas encore arrivé ?
                # leur dire de faire la routine
                # juste verifie avant si il ont drop les ressources ? mais ducoup on drop tout ou on fait un drop intelligent ?
                # leur dire de faire l'incantation
        # for player_array in player.array_uuid:
        #     if str(player_array["job"]) == EnumOrder.NOTHING.value and player_array["pos"] == 0:
        #         player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player_array["uuid"] + " " + EnumOrder.SQUARE_COLLECT.value, False)
        #         while (1):
        #             pass

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
