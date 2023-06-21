from ai.src.player import *

def take_far(player, _):
    print("take_far")
    from ai.src.order.take_around import look_item, first_pattern, second_pattern
    from ai.src.player import EnumDirection, EnumObject
    from ai.src.priority_order.ping import ping
    from ai.src.order.dump_item import dump_item
    ping(player)
    print("DANS LE TAKE AROUND mon uuid ", player.uuid)
    for i in range(5):
        player.move()
    list_item = []
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
    # player.turn(EnumDirection.LEFT.value)
    # player.turn(EnumDirection.LEFT.value)
    for i in range(5):
        player.move()
    dump_item(player, "")
    player.job = 0
    ping(player)
    print("je recois dans look_item", look_item(player))
