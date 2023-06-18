from ai.src.order.dump_item import *
from ai.src.player import *

def look_item(player):
    str: str = player.look()
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
    print("foot_case ", foot_case)
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
            for j in list_item[counter]:
                player.take(j)
            counter += 1
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
        player.move()

def init_take_around(player):
    from ai.src.player import EnumOrder
    player.job = int(EnumOrder.TAKE_AROUND.value)

def take_around(player, _):
    init_take_around(player)
    from ai.src.player import EnumDirection, EnumObject
    list_item = []
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

    first_pattern(list_item, player, EnumDirection.RIGHT)
    second_pattern(list_item[2:], player)
    if (dump_item(player) == False):
        return False
    print("je suis le boss et j'ai fini mon tour j'ai tout jeté au sol")
