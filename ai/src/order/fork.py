from ai.src.player import *

def fork_order(player):
    from ai.src.player import EnumOrder
    player.job = int(EnumOrder.FORK.value)
    player.fork()
    return True
