from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.order.check_ressources import check_ressources
from ai.src.group_init import find_boss
from ai.src.player import ALL
from ai.src.order.level_up import level_up

def msg_create(sender: Player, receiver: str, header: str, order: str = None, data: str = "Nothing") -> str:
    if (order != None):
        return (sender.uuid + " " + header + " " + receiver + " " + order + " " + data)
    else:
        return (sender.uuid + " " + header + " " + receiver + " " + data)

def boss_routine(player: Player):
    available_ai = []
    for i in player.array_uuid:
        player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.JOIN_BOSS.value, False)
        player.job = EnumOrder.JOIN_BOSS.value
    while True:
        ressources_boss_case = -2
        for player_array in player.array_uuid:
            if str(player_array["job"]) == EnumOrder.NOTHING.value and player_array["pos"] == 0:
                available_ai.append(player_array)
        if (len(available_ai) > 0):
            ressources_boss_case = check_ressources(player, player.level, available_ai)
        print("check ressources :", ressources_boss_case, "len available ai :", len(available_ai))
        if len(available_ai) > 0  and ressources_boss_case == 1:
            print("--------------BOSS ORDER LVLUP----------------")
            # tout le temps faire avancer le boss (pour pas qu'il lvl up sinon il est bloque pendant trop de temps)
            # Preciser attention a quel IA de lvl up 
            # revenir sur la case du boss
            for player_array in available_ai:
                player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player_array["uuid"] + " " + EnumOrder.INCANTATION.value, False)
                available_ai.remove(player_array)
            # player.job = EnumOrder.INCANTATION.value
            # level_up(player)
            # player.job = EnumOrder.NOTHING.value
        elif len(available_ai) > 0 and ressources_boss_case == 0:
            print("--------------BOSS ORDER GO COLLECT----------------")
            for player_array in available_ai:
                # il faudrat faire le look at me d'abord
                # puis envoyer les 4 premieres IA en routine avec une orientation diff
                # puis envoyer les 2 autres en routine diagonale
                # envoyer le boss en routine take_around ?
                player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player_array["uuid"] + " " + EnumOrder.SQUARE_COLLECT.value, False)
                player_array["job"] = EnumOrder.SQUARE_COLLECT.value
                available_ai.remove(player_array)
        elif len(available_ai) > 0 and ressources_boss_case == -1:
            print("--------------BOSS ORDER FORK----------------")
            # Leur demander de FORK
            # gerer le fork
        else:
            player.broadcast(player.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " Venez m'aider !", False)

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
