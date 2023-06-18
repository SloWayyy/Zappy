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

def can_level_up(player, boss_case):
    from ai.src.player import levelUpArray

    count = 0
    nbr_player = boss_case[0] - 1

    for i in levelUpArray[player.level - 1]:
        if count == 0:
            if i >= boss_case[count]:
                return -1
        elif count == 1:
            if (i * nbr_player) > (boss_case[count]):
                return 0
        else:
            if i > (boss_case[count]):
                return 0
        count += 1

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

def order_bigger_player(player, array_bigger_level):
    pass

def handle_incantation(player):
    available_ai = get_available_ia(player)
    boss_case = get_ressources(player)
    minus_level = check_minus_level(available_ai)
    array_bigger_level, array_minus_level = check_same_level(available_ai, minus_level)
    



    can_level_up(player, boss_case)
    print("ressources ok")
    return 1
