from ai.src.player import *
from ai.src.order.take_around import *
from enum import Enum

# ne pas faire lvl up les BOSS il doit toujours ce decaler
# ne prendre en compte que les IA qui ne sont pas des forksfarmer (verifier dans l'array_uuid)
# verifier si tous les aviable ai sont du meme lvl
# si oui, verifier si on a assez de ressources pour lvl up (il faut verifier par rapport au niveau la nos calculs
# sont pas bon quand c une elevation a plusieurs il faut le nombre de ressources indiqués et pas le nombre de ressources
# * le nombre de joueurs (exeption pour le niveau 1)))
# sinon elle ne sont pas du meme lvl, il faut envoyer les plus haut lvl en routine
# et pendant ce temps tu verif si les plus bas niveau ont assez de ressources pour lvl up
# si oui tu les lvl up et qu'ils sont assez
# si ils sont pas assez tu leurs demande de fork
# si ils sont assez mais pas assez de ressources tu les envoies en routine

def get_available_ia(player):
    from ai.src.player import EnumOrder
    available_ai = []
    for player_array in player.array_uuid:
        if str(player_array["job"]) == EnumOrder.NOTHING.value and player_array["pos"] == 0:
            available_ai.append(player_array)
    return available_ai

def get_ressources(player):
    from ai.src.player import EnumObject
    _, foot_case = look_item(player)
    boss_case = []
    boss_case.append(foot_case.count("player"))
    for i in EnumObject:
        boss_case.append(foot_case.count(i.value))
    return boss_case

def check_minus_level(available_ia):
    minus_level = 10

    for player in available_ia:
        if player["level"] < minus_level:
            minus_level = player["level"]
    return minus_level

def check_same_level(available_ia, minus_level):
    array_bigger_level = []
    array_minus_level = []
    for player in available_ia:
        if player["level"] != minus_level:
            array_bigger_level.append(player)
        else:
            array_minus_level.append(player)
    return array_bigger_level, array_minus_level



def send_them_in_routine(boss, array_player):
    from ai.src.player import EnumOrder, EnumHeader
    from ai.src.game import msg_create
    count = 0
    order = EnumHeader.ORDER.value
    # call look at me here
    for player in array_player:
        print("len: ", len(array_player))
        if count == 0:
            print("order 0")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.SQUARE_COLLECT.value, "1"))
        elif count == 1:
            print("order 1")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.SQUARE_COLLECT.value, "3"))
        elif count == 2:
            print("order 2")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.SQUARE_COLLECT.value, "7"))
        elif count == 3:
            print("order 3")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.SQUARE_COLLECT.value, "5"))
        elif count == 4:
            print("order 4")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.TAKE_AROUND.value))
        elif count == 5:
            print("order 5")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.GO_FRONT.value, "1"))
        elif count == 6:
            print("order 6")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.GO_FRONT.value, "7"))
        else:
            print("order 7")
            boss.broadcast(msg_create(boss, player["uuid"], order, EnumOrder.TAKE_AROUND.value))
        count += 1

def handle_result_level_up(player, result):
    from ai.src.game import msg_create
    from ai.src.player import EnumOrder, EnumHeader
    if result == -1:
        msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.FORK.value)
    elif result == 0:
        msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.SQUARE_COLLECT.value)
    else:
        msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.LEVEL_UP.value)

class Answer(Enum):
    INCANTATION = 1
    ROUTINE = 2
    FORK = 3
    NOTHING = 4

def handle_level_up(actual_lvl, boss_case, nbr_player):
    from ai.src.player import levelUpArray

    if (nbr_player == 0):
        return Answer.NOTHING.value, 0
    if (actual_lvl == 1):
        if (boss_case[2] < levelUpArray[0][2] * nbr_player):
            return Answer.ROUTINE.value, 0
        else:
            return Answer.INCANTATION.value, 0
    if (nbr_player < levelUpArray[actual_lvl - 1][0]):
        return Answer.FORK.value, levelUpArray[actual_lvl - 1][0] % nbr_player
    # il lui dit de fork et de combien de personne on doit fork comme ca les autres vont en routine
    # print("CASE A COMPARER:", levelUpArray[actual_lvl - 1])
    for i in range(len(levelUpArray[0])):
        # print("je compare", boss_case[i], "avec", levelUpArray[actual_lvl - 1][i])
        if (boss_case[i] * (nbr_player // levelUpArray[actual_lvl - 1][0]) < levelUpArray[actual_lvl - 1][i] * (nbr_player // levelUpArray[actual_lvl - 1][0])):
            print("j'ai PAS ASSEZ DE RESSOURCES POUR PASSER LVL", actual_lvl + 1, "boss cass", boss_case)
            return Answer.ROUTINE.value, 0
    print("je LEU DIT DE LVL UP VOICI l'inventaire", boss_case, "et le lvl", actual_lvl + 1)
    return Answer.INCANTATION.value, 0

def handle_incantation(boss):
    from ai.src.game import msg_create
    from ai.src.player import EnumOrder, EnumHeader, EnumObject

    # if (boss.incanteur_uuid != []):
    #     for player in boss.array_uuid:
    #         # print("je rentre ici", boss.incanteur_uuid, flush=True)
    #         # print("boss.array_uuid", boss.array_uuid, flush=True)
    #         if (player["uuid"] == boss.incanteur_uuid[0][0] and int(player["level"]) - 1 == int(boss.incanteur_uuid[0][1])):
    #             print("JE RENTRE LA-------------------------------------------")
    #             for player_new_lvl in boss.array_uuid:
    #                 # print("comparaison :  ", player_new_lvl["level"], player["level"])
    #                 if (player_new_lvl["level"] == player["level"] - 1 and player_new_lvl["uuid"] != player["uuid"]):
    #                     print("je lui monte le lvl")
    #                     player_new_lvl["level"] = player["level"]
    #             boss.incanteur_uuid = []
    #             # print("quand je sors ", boss.array_uuid, flush=True)
    #             break
    available_ai = get_available_ia(boss)
    for player in boss.array_uuid:
        # print("player: ", player["uuid"], "lvl", player["level"])
        if (str(player["job"]) == EnumOrder.LEVEL_UP.value):
            # print("je rentre la ?")
            return 0
    if (len(available_ai) != len(boss.array_uuid)):
        return 0
    boss_case = get_ressources(boss)
    minus_level = check_minus_level(available_ai)
    array_bigger_level, array_minus_level = check_same_level(available_ai, minus_level)
    print("available ia", available_ai, flush=True)
    if (len(array_minus_level) == 0):
        return 0
    result, nbr_fork = handle_level_up(minus_level, boss_case, len(array_minus_level))
    if boss_case[1] != 0:
        boss.take(EnumObject.FOOD.value)

    print("boss.array:", boss.array_uuid, flush=True)
    if (len(array_bigger_level) == 0 and result == Answer.INCANTATION.value):
        if (array_minus_level[0]["level"] == 1):
            for player in array_minus_level:
                boss.broadcast(msg_create(boss, player["uuid"], EnumHeader.ORDER.value, EnumOrder.LEVEL_UP.value))
        elif array_minus_level[0]["level"] == 2 or array_minus_level[0]["level"] == 3:
            print("je lui dit de lvl up", flush=True)
            for i in range (len(array_minus_level) // 2):
                boss.broadcast(msg_create(boss, array_minus_level[i]["uuid"], EnumHeader.ORDER.value, EnumOrder.LEVEL_UP.value))
                boss.incanteur_uuid.append((array_minus_level[i]["uuid"], array_minus_level[i]["level"]))
        elif array_minus_level[0]["level"] == 4 or array_minus_level[0]["level"] == 5:
            for i in range (len(array_minus_level) // 4):
                boss.broadcast(msg_create(boss, array_minus_level[i]["uuid"], EnumHeader.ORDER.value, EnumOrder.LEVEL_UP.value))
                boss.incanteur_uuid.append((array_minus_level[i]["uuid"], array_minus_level[i]["level"]))

    elif (len(array_bigger_level) == 0 and result == Answer.FORK.value):
        for player in range(len(array_minus_level)):
            if (player < nbr_fork):
                boss.broadcast(msg_create(boss, array_minus_level[player]["uuid"], EnumHeader.ORDER.value, EnumOrder.FORK.value))
            else:
                boss.broadcast(msg_create(boss, array_minus_level[player]["uuid"], EnumHeader.ORDER.value, EnumOrder.SQUARE_COLLECT.value, "1"))
    elif (len(array_bigger_level) == 0 and result == Answer.ROUTINE.value):
        send_them_in_routine(boss, array_minus_level)
    else:
        print("je suis dans le else 4")
        send_them_in_routine(boss, array_minus_level)

    # Ramasser la bouffe au sol (le boss)
    if ((array_minus_level[0]["level"]) == 1):
        take_around(boss, 4)
    print("\n")
    return 1
