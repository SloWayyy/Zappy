from ai.src.order.dump_item import *

def level_up(player):
    if (dump_item(player) == False):
        return False
    print("lvl up :", player.incantation())

    print("level_up")
