from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder, EnumPriorityOrder
from ai.src.order.check_ressources import check_ressources
from ai.src.group_init import find_boss
from ai.src.player import ALL
from time import sleep

def boss_routine(player: Player):
    for i in player.array_uuid:
        player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.JOIN_BOSS.value, False)
        player.job = EnumOrder.JOIN_BOSS.value
    while True:
        tmp = check_ressources(player)
        print("check ressources :", tmp)
        if str(player.array_uuid[0]["job"]) == EnumOrder.NOTHING.value and tmp == 1:
            print("--------------boss routine 1----------------")
            player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.INCANTATION.value, False)
            player.job = EnumOrder.INCANTATION.value
            exit(0)
        elif str(player.array_uuid[0]["job"]) == EnumOrder.NOTHING.value:
            player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + i["uuid"] + " " + EnumOrder.SQUARE_COLLECT.value, False)
            player.job = EnumOrder.SQUARE_COLLECT.value
        else:
            player.broadcast(player.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " Venez m'aider !", False)

                # faire la routine boss ? mais si tout le monde n'est pas encore arrivé ?
                # leur dire de faire la routine
                # juste verifie avant si il ont drop les ressources ? mais ducoup on drop tout ou on fait un drop intelligent ?
                # leur dire de faire l'incantation
        # for player_array in player.array_uuid:
        #     if str(player_array["job"]) == EnumOrder.NOTHING.value and player_array["pos"] == 0:
        #         print("j'appel square collect")
        #         player_array["job"] = EnumOrder.SQUARE_COLLECT.value
            # if
                # while (1):
                #     check_ressources(player)
                #     # # tmp = check_ressources(player_array)
                #     # # print("check ressources :", tmp)
                #     # if check_ressources(player_array) == 1:
                #     #     print("j'appel incantation")
                #     #     # player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player_array["uuid"] + " " + EnumOrder.INCANTATION.value, False)
                #     #     # player_array["job"] = EnumOrder.INCANTATION.value
                #     #     pass
                #     pass

def game_loop(sock, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
