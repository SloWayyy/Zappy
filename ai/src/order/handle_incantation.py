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
    print("boss_case", boss_case)
    return boss_case

def handle_level_up(array_minus_level, minus_level, boss_case):
    from ai.src.player import levelUpArray
    count = 0

    for i in levelUpArray[minus_level - 1]:
        if count == 0:
            if i >= boss_case[count]:
                return -1
        else:
            if i > (boss_case[count]):
                return 0
        count += 1
    return 1

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

def send_them_in_routine(player, array_bigger_level):
    from ai.src.game import msg_create
    count = 0
    # call look at me here
    for player in array_bigger_level:
        if count <= 4:
            msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.SQUARE_COLLECT.value)
        elif count == 5:
            msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.TAKE_AROUND.value)
        else:
            msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.GO_FRONT.value)

def handle_result_level_up(player, result):
    from ai.src.game import msg_create
    from ai.src.player import EnumOrder
    if result == -1:
        msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.FORK.value)
    elif result == 0:
        msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.SQUARE_COLLECT.value)
    else:
        msg_create(player, player["uuid"], EnumHeader.ORDER.value, EnumOrder.INCANTATION.value)

def handle_incantation(player):
    available_ai = get_available_ia(player)
    boss_case = get_ressources(player)
    minus_level = check_minus_level(available_ai)
    array_bigger_level, array_minus_level = check_same_level(available_ai, minus_level)
    send_them_in_routine(player, array_bigger_level)
    result = handle_level_up(array_minus_level, minus_level, boss_case)
    handle_result_level_up(player, result)
    print("ressources ok")
    return 1
