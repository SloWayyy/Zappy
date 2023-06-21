from ai.src.order.dump_item import *
from ai.src.player import *

def look_item(player):
    str: str = player.look(True)
    print("LOOK: {}".format(str))
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
    print("FOOT CASE DANS LOOK: {}".format(foot_case))
    return list_tmp[:3], foot_case

def first_pattern(list_item : list, player, direction):
    player.move()
    if (list_item == []):
        return
    for i in list_item[0]:
        player.take(i)
    player.turn(direction)
    player.move()
    for i in list_item[1]:
        player.take(i)

def second_pattern(list_item : list, player):
    from ai.src.player import EnumDirection
    counter = 0

    for _ in range(0, 3):
        player.turn(EnumDirection.RIGHT)
        for _ in range(0, 2):
            player.move()
            if (counter < len(list_item)):
                for j in list_item[counter]:
                    player.take(j)
                counter += 1
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
        player.move()

def take_around(player, routine = False):
    from ai.src.player import EnumDirection, EnumObject
    from ai.src.priority_order.ping import ping
    ping(player)
    list_item = []

    #pk il prend food ici ?

    player.take(EnumObject.FOOD.value)
    for i in range(0, 4):
        tmp, _ = look_item(player)
        for j in tmp:
            list_item.append(j)
        if (player.turn(EnumDirection.RIGHT) == False):
            return False
    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2
    # le 4 a changer
    if (len(list_item) < 6):
        ping(player)
        return False
    first_pattern(list_item, player, EnumDirection.RIGHT)
    second_pattern(list_item[2:], player)
    if (routine == False and dump_item(player, 4) == False):
        return False
    return True
