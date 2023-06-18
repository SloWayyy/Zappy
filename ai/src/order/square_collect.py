from ai.src.order.take_around import *
from ai.src.order.dump_item import *

def first_pattern_ai(list_item: list, player):
    from ai.src.player import EnumDirection
    player.move()
    for i in list_item[0]:
        player.take(i)
    player.turn(EnumDirection.LEFT)
    player.move()
    for i in list_item[1]:
        player.take(i)

def second_pattern_ai(list_item: list, player):
    from ai.src.player import EnumDirection
    player.turn(EnumDirection.LEFT)
    player.move()
    player.move()
    for i in list_item[0]:
        player.take(i)
    player.turn(EnumDirection.LEFT)
    player.move()
    for i in list_item[1]:
        player.take(i)
    player.move()
    for i in list_item[2]:
        player.take(i)
    player.turn(EnumDirection.LEFT)
    player.move()
    player.move()
    for i in list_item[3]:
        player.take(i)

def look_aroud_ai(player):
    from ai.src.player import EnumDirection
    list_item = []
    for _ in range(0, 3):
        player.move()
    tmp, foot_case = look_item(player)
    for i in tmp:
        list_item.append(i)
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
    tmp, _ = look_item(player)
    for j in tmp:
        list_item.append(j)
    if (len(list_item) > 1):
        list_item.insert(0, list_item.pop())
    return list_item, foot_case

def return_to_boss(player):
    from ai.src.player import EnumDirection
    if (player.turn(EnumDirection.LEFT) == False):
        return False
    if (player.move() == False):
        return False
    if (player.turn(EnumDirection.RIGHT) == False):
        return False
    if (player.move() == False):
        return False
    if (player.move() == False):
        return False

def look_this_orientation(player, orientation: int):
    from ai.src.player import EnumDirection
    if orientation == 3:
        return (player.turn(EnumDirection.LEFT))
    elif orientation == 5:
        if (player.turn(EnumDirection.LEFT) == False):
            return False
        return (player.turn(EnumDirection.LEFT))
    elif orientation == 7:
        return (player.turn(EnumDirection.RIGHT))
    else:
        return True

def square_collect(player, data):
    orientation = int(data)
    list_item, _ = look_aroud_ai(player)
    if (look_this_orientation(player, orientation) == False):
        return False
    list_item.reverse()
    first_pattern_ai(list_item, player)
    second_pattern_ai(list_item[2:], player)
    if (return_to_boss(player) == False):
        return False
    if (dump_item(player) == False):
        return False
    print("(AI) je suis arrivé au boss et j'ai déposé mes items")
