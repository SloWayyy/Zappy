from ai.src.player import Player
from ai.src.order.dump_item import dump_item

def level_up(player: Player):
    if (dump_item(player) == False):
        return False
    print("lvl up :", player.incantation())

    print("level_up")
