from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.order.handle_incantation import handle_incantation
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
        # player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.JOIN_BOSS.value, False)
        player.broadcast(msg_create(player, i["uuid"], EnumHeader.ORDER.value, EnumOrder.JOIN_BOSS.value))
        # player.job = EnumOrder.JOIN_BOSS.value
    while True:
            player.broadcast(msg_create(player, ALL, EnumHeader.IMBOSS.value))
            handle_incantation(player)
            print(player.array_uuid)
            # msg_create(player, ALL, EnumHeader.IMBOSS.value)
            # print("je suis la")
        # ressources_boss_case = -2

        # if (len(available_ai) > 0):
        # print("check ressources :", ressources_boss_case, "len available ai :", len(available_ai))
        # if len(available_ai) > 0  and ressources_boss_case == 1:
        #     print("--------------BOSS ORDER LVLUP----------------")
        #     # tout le temps faire avancer le boss (pour pas qu'il lvl up, sinon il est bloque pendant trop de temps).
        #     # Préciser, attention a quel IA de lvl up.
        #     # Revenir sur la case du boss.
        #     for player_array in available_ai:
        #         # player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player_array["uuid"] + " " + EnumOrder.INCANTATION.value, False)
        #         msg_create(player, player_array["uuid"], EnumHeader.ORDER.value, EnumOrder.INCANTATION.value)
        #         available_ai.remove(player_array)
        #     # player.job = EnumOrder.INCANTATION.value
        #     # level_up(player)
        #     # player.job = EnumOrder.NOTHING.value
        # elif len(available_ai) > 0 and ressources_boss_case == 0:
        #     print("--------------BOSS ORDER GO COLLECT----------------")
        #     for player_array in available_ai:
        #         # il faudrat faire le look at me d'abord
        #         # puis envoyer les 4 premieres IA en routine avec une orientation diff
        #         # puis envoyer les 2 autres en routine diagonale
        #         # envoyer le boss en routine take_around ?
        #         # player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player_array["uuid"] + " " + EnumOrder.SQUARE_COLLECT.value, False)
        #         msg_create(player, player_array["uuid"], EnumHeader.ORDER.value, EnumOrder.SQUARE_COLLECT.value)
        #         player_array["job"] = EnumOrder.SQUARE_COLLECT.value
        #         available_ai.remove(player_array)
        # elif len(available_ai) > 0 and ressources_boss_case == -1:
        #     print("--------------BOSS ORDER FORK----------------")
        #     # Leur demander de FORK
        #     # gerer le fork
        # else:
            # player.broadcast(player.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " Venez m'aider !", False)
            # msg_create(player, ALL, EnumHeader.ORDER.value, EnumOrder.JOIN_BOSS.value)
            # msg_create(player, i["uuid"], EnumHeader.ORDER.value, EnumOrder.JOIN_BOSS.value)

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
