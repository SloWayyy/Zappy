from ai.src.player import *

def get_arround(player):
    from ai.src.order.take_around import look_item, first_pattern, second_pattern
    from ai.src.player import EnumDirection
    list_item = []
    for i in range(0, 4):
        tmp, foot_case = look_item(player)
        for j in tmp:
            list_item.append(j)
        if (player.turn(EnumDirection.RIGHT) == False):
            return False
    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2

    for i in foot_case:
        if (i != "player"):
            player.take(i)
    first_pattern(list_item, player, EnumDirection.RIGHT)
    second_pattern(list_item[2:], player)

def take_far(player, _):
    from ai.src.player import EnumObject
    from ai.src.priority_order.ping import ping
    from ai.src.order.dump_item import dump_item
    ping(player)
    for i in range(3):
        player.move()
    get_arround(player)
    for i in range(3):
        player.move()
    dump_item(player, "")
    # supprimer ? le frop
    player.job = 0
