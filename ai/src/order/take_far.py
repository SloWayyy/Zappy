from ai.src.player import *

def take_far(player, _):
    print("take_far")
    from ai.src.order.take_around import take_around, look_item
    for i in range(5):
        player.move()
    # take_around(player, True)
    print(look_item(player))
    exit(0)
