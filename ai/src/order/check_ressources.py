from ai.src.player import *
from ai.src.order.take_around import *
from enum import Enum

def check_ressources(player):
    from ai.src.player import EnumObject, levelUpArray
    _, foot_case = look_item(player)
    boss_case = []
    boss_case.append(foot_case.count("player"))
    for i in EnumObject:
        boss_case.append(foot_case.count(i.value))
    count = 0
    print("boss_case", boss_case)
    for i in levelUpArray[player.level - 1]:
        if count == 0:
            if i >= boss_case[count]:
                return -1
        else:
            if (i * boss_case[0]) > (boss_case[count]):
                return 0
        count += 1
    print("ressources ok")
    return 1
