from ai.src.player import *
from ai.src.order.take_around import *


def check_ressources(player):
    from ai.src.player import EnumObject, EnumOrder, EnumPriorityOrder
    _, foot_case = look_item(player)
    print("j'ai rien au sol freort:", foot_case)
    boss_case = []
    boss_case.append(foot_case.count("player"))
    for i in EnumObject:
        boss_case.append(foot_case.count(i.value))
    print(boss_case)