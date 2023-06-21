from ai.src.player import *

def take_far(player, _):
    from ai.src.order.take_around import look_item, first_pattern, second_pattern
    from ai.src.player import EnumDirection, EnumObject
    from ai.src.priority_order.ping import ping
    from ai.src.order.dump_item import dump_item
    ping(player)
    for i in range(5):
        player.move()
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
    for i in range(5):
        player.move()
    dump_item(player, "")
    player.job = 0
