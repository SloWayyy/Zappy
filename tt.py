from enum import Enum

class EnumObject (Enum):
    FOOD = "food"
    LINEMATE = "linemate"
    DERAUMERE = "deraumere"
    SIBUR = "sibur"
    MENDIANE = "mendiane"
    PHIRAS = "phiras"
    THYSTAME = "thystame"

def look_item():
    str: str = "[player player player player player player player player player food food food food food food food linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate deraumere deraumere deraumere deraumere deraumere deraumere deraumere deraumere deraumere deraumere deraumere deraumere deraumere sibur sibur sibur sibur sibur mendiane mendiane mendiane mendiane mendiane mendiane mendiane mendiane mendiane phiras phiras phiras phiras phiras phiras thystame,,sibur,]"
    # print("RETOUR DU BUG DE RAYAN OMG ?", str, flush=True)
    str = str.replace("[", "")
    str = str.replace(",]", ",V")
    str = str.replace("]", "")
    for i in range(0, 10):
        str = str.replace(",,", ",V,")
    list : list = str.split(",")
    list_tmp = []
    for i in list:
        list_tmp.append(i.split(" "))
    foot_case = list_tmp.pop(0)
    return list_tmp[:3], foot_case

_, foot_case = look_item()
boss_case = []
boss_case.append(foot_case.count("player"))
for i in EnumObject:
    boss_case.append(foot_case.count(i.value))
print("case: ", boss_case, flush=True)
